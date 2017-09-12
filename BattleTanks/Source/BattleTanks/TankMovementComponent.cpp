// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(const float& Throw) const
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(const float& Throw) const
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();

	auto forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	IntendMoveForward(forwardThrow);

	auto rightThrow = FVector::CrossProduct(aiForwardIntention, tankForward).Z;
	IntendTurnRight(-rightThrow);
}

