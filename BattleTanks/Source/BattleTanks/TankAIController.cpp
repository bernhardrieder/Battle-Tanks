// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

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

	ATank* PlayerTank = GetPlayerTank();
	if(PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI %s found Player %s"), *Tank->GetName(), *PlayerTank->GetName());
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATankPlayerController* playerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	return playerController ? Cast<ATank>(playerController->GetControlledTank()) : nullptr;
}

void ATankAIController::AimTowardsPlayer()
{
	if (ATank* player = GetPlayerTank())
	{

	}
	else
		return;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
