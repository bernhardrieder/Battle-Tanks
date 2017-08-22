// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(const float& RelativeSpeed)
{
	//move the barrel the right amount this frame
	//given a max elevtion speed, and the frame time
	const float relativeSpeedClamped = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto elevationChange = relativeSpeedClamped *MaxDegreesPerSecond *GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0, 0));
}