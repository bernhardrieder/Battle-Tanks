// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATankBarrelProjectile::ATankBarrelProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	MovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ATankBarrelProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankBarrelProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankBarrelProjectile::LaunchProjectile(const float& Speed)
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	MovementComponent->Activate();
}

