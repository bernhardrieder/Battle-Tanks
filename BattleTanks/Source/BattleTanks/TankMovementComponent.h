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
	UFUNCTION(BlueprintCallable, Category = "Movement") //DON'T MAKE THIS CONST -> breaks BP flow
	void IntendMoveForward(const float& Throw);

	UFUNCTION(BlueprintCallable, Category = "Movement") //DON'T MAKE THIS CONST -> breaks BP flow
	void IntendTurnRight(const float& Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(class UTankTrack* LeftTrack, class UTankTrack* RightTrack);

private:
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	class UTankTrack* LeftTrack = nullptr;
	class UTankTrack* RightTrack = nullptr;
	
};
