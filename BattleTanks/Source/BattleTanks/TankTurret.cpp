// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(const float& RelativeSpeed)
{
	const float relativeSpeedClamped = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float rotationChange = relativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rotatin = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0, rotatin, 0));
}
