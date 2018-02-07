// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is player controlled"), *ControlledTank->GetName())
	}
	else UE_LOG(LogTemp, Error, TEXT("No tank is player controlled"))
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;
	FVector HitLocation; //OUT parameter
	if (GetHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString())
	}
}
bool ATankPlayerController::GetHitLocation(FVector &OutHitLocation) const
{
	///find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY; //OUT parameters
	GetViewportSize(ViewportSizeX, ViewportSizeY); //overwriting OUT parameters
	FVector2D ScreenLocation = FVector2D(CrosshairXPos*ViewportSizeX, CrosshairYPos*ViewportSizeY);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LookDirection.ToString())
	}
	//overwrite HitLocation with result
	OutHitLocation = FVector(1.0);
	//if HitLocation is null
	return false;
	//else return true
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; //discarded later
	return DeprojectScreenPositionToWorld(ScreenLocation[0], ScreenLocation[1], WorldLocation, LookDirection);
}