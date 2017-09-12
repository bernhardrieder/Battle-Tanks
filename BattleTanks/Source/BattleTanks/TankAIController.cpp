// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledTank = Cast<ATank>(GetPawn());

	if(playerTank)
	{
		MoveToActor(playerTank, AcceptanceRadius);

		controlledTank->AimAt(playerTank->GetActorLocation());

		controlledTank->Fire();
	}
}
