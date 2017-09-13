// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

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
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>("Impact Blast");
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>("Explosion Force");
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionForce->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ATankBarrelProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &ATankBarrelProjectile::OnHit);
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

void ATankBarrelProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ATankBarrelProjectile::OnDestroyTimerExpired, DestroyDelay, false);
}

void ATankBarrelProjectile::OnDestroyTimerExpired()
{
	Destroy();
}

