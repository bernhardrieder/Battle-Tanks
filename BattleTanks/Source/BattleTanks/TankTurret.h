// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 25.f;
	
public:
	void Rotate(const float& RelativeSpeed);
};
