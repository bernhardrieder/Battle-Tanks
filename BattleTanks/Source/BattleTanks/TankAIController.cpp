// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if(Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not possessing a tank!"));
	}
}
