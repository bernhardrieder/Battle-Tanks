// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATankBarrelProjectile::ATankBarrelProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	MovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("CollisionMesh");
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>("Launch Blast");
	auto attachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	LaunchBlast->AttachToComponent(RootComponent, attachmentRules);
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

