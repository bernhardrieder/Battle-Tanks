// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include!!!


class UTankAimingComponent;

/**
 * Responsible for helping the player 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnPossesedTankDeath();

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn* InPawn) override;
private:
	UPROPERTY(EditDefaultsOnly)
	FVector2D CrosshairLocationInViewport = FVector2D(0.5f, 0.33f);

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000; //10 km == 10 000 m == 10 000 00 cm

	class UTankAimingComponent* AimingComponent = nullptr;
};
