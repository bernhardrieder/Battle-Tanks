// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(const FVector& Location, const float& ProjectileLaunchSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s is aiming at %s"), *(GetOwner()->GetName()), *Location.ToString());

	if (!Barrel || !Turret) return;

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

		//UE_LOG(LogTemp, Warning, TEXT("Fire with LaunchSpeed = %f"), LaunchSpeed);

		FVector aimDirection = outLaunchDirection.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* TankBarrel)
{
	if(TankBarrel)
		Barrel = TankBarrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TankTurret)
{
	if(TankTurret)
		Turret = TankTurret;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	//work-out difference between current barrel rotation and aimdirection
	FRotator barrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator aimRotation = AimDirection.Rotation();
	FRotator deltaRotation = aimRotation - barrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("Aim Rotation = %s"), *aimRotation.ToString());


	Barrel->Elevate(deltaRotation.Pitch);
	Turret->Rotate(deltaRotation.Yaw);
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

