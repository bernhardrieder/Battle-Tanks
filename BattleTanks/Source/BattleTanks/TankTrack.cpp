// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(const float& Throttle)
{
	//auto name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle = %f"), *name, FMath::Clamp(Throttle, -1.f, 1.f));

	auto forceApplied = GetForwardVector() * FMath::Clamp(Throttle, -1.f, 1.f) * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}
