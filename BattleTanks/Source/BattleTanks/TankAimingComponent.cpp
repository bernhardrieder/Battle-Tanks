// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "TankBarrelProjectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(const FVector& Location)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;

	FVector outLaunchDirection = FVector::ZeroVector;
	auto startPos = Barrel->GetSocketLocation(FName("Output"));
	if (UGameplayStatics::SuggestProjectileVelocity(this,
		outLaunchDirection,
		startPos,
		Location,
		ProjectileLaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)
		)
	{

		FVector aimDirection = outLaunchDirection.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (ensure(BP_Projectile) && ensure(Barrel) && isReloaded)
	{
		ATankBarrelProjectile* projectile = GetWorld()->SpawnActor<ATankBarrelProjectile>(BP_Projectile, Barrel->GetSocketTransform(FName("Output")));
		projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!ensure(Barrel)) return;
	//work-out difference between current barrel rotation and aimdirection
	FRotator barrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator aimRotation = AimDirection.Rotation();
	FRotator deltaRotation = aimRotation - barrelRotation;

	Barrel->Elevate(deltaRotation.Pitch);
	Turret->Rotate(deltaRotation.Yaw);

	FiringStatus = deltaRotation.Pitch == 0.f && deltaRotation.Yaw == 0.f ? EFiringStatus::Locked : EFiringStatus::Aiming;
}
