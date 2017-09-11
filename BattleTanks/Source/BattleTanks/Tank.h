// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileLaunchSpeed = 4000; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	//UClass* ProjectileBP;
	TSubclassOf<class ATankBarrelProjectile> BP_Projectile;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(const FVector& Location);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(class UTankBarrel* TankBarrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(class UTankTurret* TankTurret);

	UFUNCTION(BlueprintCallable, Category = "Tank Actions")
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	class UTankBarrel* Barrel;

	float LastFireTime = 0.f;

};
