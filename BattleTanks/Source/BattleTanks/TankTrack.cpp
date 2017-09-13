// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(const float& Throttle)
{
	auto forceApplied = GetForwardVector() * FMath::Clamp(Throttle, -1.f, 1.f) * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//calculate the slippage speed
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//work-out the required acceleration this frame to correct
	auto correctionAcceleration = (-slippageSpeed / DeltaTime) * GetRightVector();

	//calculate and apply sideways for (F = m a)
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2.f; //two tracks
	tankRoot->AddForce(correctionForce);
}

