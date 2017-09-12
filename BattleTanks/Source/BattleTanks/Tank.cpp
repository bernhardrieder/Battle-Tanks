// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "TankBarrelProjectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::AimAt(const FVector& Location)
{
	AimingComponent->AimAt(Location, ProjectileLaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* TankBarrel)
{
	AimingComponent->SetBarrelReference(TankBarrel);
	Barrel = TankBarrel;
}

void ATank::SetTurretReference(UTankTurret* TankTurret)
{
	AimingComponent->SetTurretReference(TankTurret);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
		ATankBarrelProjectile* projectile = GetWorld()->SpawnActor<ATankBarrelProjectile>(BP_Projectile, Barrel->GetSocketTransform(FName("Output")));
		projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

