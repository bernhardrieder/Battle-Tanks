// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (ATank* tank = GetControlledTank())
	{
		FVector hitLocation;
		if (GetSightRayHitLocation(hitLocation))
		{
			tank->AimAt(hitLocation);
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair location in pixel coordinates
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation = FVector2D(viewportSizeX*CrosshairLocationInViewport.X, viewportSizeY*CrosshairLocationInViewport.Y);
	

	FVector cameraWorldLocation, lookDirection;
	
	//get look direction
	if(DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection))
	{
		if (GetLookVectorHitLocation(lookDirection, OutHitLocation))
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + LookDirection*LineTraceRange;

	if(GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = hitResult.Location;
		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}
