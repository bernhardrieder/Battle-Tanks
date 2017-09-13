// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forced to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.f; // assumem 40 tonne tank, 1g acceleration

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(const float& Throttle);

	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void ApplySidewaysForce();
	void DriveTrack();

private:
	float CurrentThrottle = 0;
};
