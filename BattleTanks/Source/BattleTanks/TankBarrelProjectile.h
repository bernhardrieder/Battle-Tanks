// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankBarrelProjectile.generated.h"

UCLASS()
class BATTLETANKS_API ATankBarrelProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* MovementComponent;
	
public:	
	// Sets default values for this actor's properties
	ATankBarrelProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(const float& Speed);
	
};