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

		AimDirection = outLaunchDirection.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (ensure(BP_Projectile) && ensure(Barrel) && (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming))
	{
		ATankBarrelProjectile* projectile = GetWorld()->SpawnActor<ATankBarrelProjectile>(BP_Projectile, Barrel->GetSocketTransform(FName("Output")));
		projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		--RoundsLeft;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!ensure(Barrel)) return;
	//work-out difference between current barrel rotation and aimdirection
	FRotator barrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator aimRotation = AimDirection.Rotation();
	FRotator deltaRotation = aimRotation - barrelRotation;

	Barrel->Elevate(deltaRotation.Pitch);
	Turret->Rotate(deltaRotation.Yaw < 180 ? deltaRotation.Yaw : -deltaRotation.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) return false;
	auto barrelForward = Barrel->GetForwardVector();
	return !barrelForward.Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(RoundsLeft <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	} 
	else if(IsBarrelMoving())
	{	
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}
