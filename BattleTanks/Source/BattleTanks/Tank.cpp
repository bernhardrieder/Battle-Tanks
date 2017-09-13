// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float ATank::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(Damage);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, CurrentHealth);

	CurrentHealth -= damageToApply;

	return damageToApply;
}

float ATank::GetCurrentHealthPercent() const
{
	return static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}
