// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UTankAimingComponent* AimingComponent;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileLaunchSpeed = 100000; //sensible starting value of 1000 m/s

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(const FVector& Location);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(class UTankBarrel* TankBarrel);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
};
