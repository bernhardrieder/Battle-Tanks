// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPossesedTankDeath();

public:
	virtual void SetPawn(APawn* InPawn) override;
private:
	//how can the ai tank get to the player tank
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 6000.f;

	class UTankAimingComponent* AimingComponent = nullptr;
};
