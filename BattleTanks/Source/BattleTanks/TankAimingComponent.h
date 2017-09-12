// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	//UClass* ProjectileBP;
	TSubclassOf<class ATankBarrelProjectile> BP_Projectile;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileLaunchSpeed = 4000;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(class UTankBarrel* Barrel, class UTankTurret* Turret);

	void AimAt(const FVector& Location);

	UFUNCTION(BlueprintCallable, Category = "Tank Actions")
	void Fire();

protected:
	void MoveBarrelTowards(const FVector& AimDirection);

private:
	class UTankBarrel* Barrel = nullptr;
	class UTankTurret* Turret = nullptr;

	float LastFireTime = 0.f;

protected:
	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;
};
