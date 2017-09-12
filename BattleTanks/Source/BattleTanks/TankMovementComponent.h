// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible from driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(const float& Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(const float& Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(class UTankTrack* LeftTrack, class UTankTrack* RightTrack);

private:
	class UTankTrack* LeftTrack = nullptr;
	class UTankTrack* RightTrack = nullptr;
	
};
