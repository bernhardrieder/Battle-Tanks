// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank!"));
	}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair location in pixel coordinates
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation = FVector2D(viewportSizeX*CrosshairLocationInViewport.X, viewportSizeY*CrosshairLocationInViewport.Y);
	
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation = %s"), *screenLocation.ToString());

	FVector cameraWorldLocation, lookDirection;
	
	if(DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction = %s"), *lookDirection.ToString());
	}
	return true;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector HitLocation;
	GetSightRayHitLocation(HitLocation);
}
