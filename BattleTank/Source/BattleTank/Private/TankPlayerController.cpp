// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
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
		FHitResult HitResult;
		float LineTraceRange = 10000000.f;
		FVector LineStart;
		FRotator ActorRot;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(LineStart, ActorRot);
		FVector LineEnd = LineStart + LookDirection * LineTraceRange;
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
		FCollisionResponseParams ResponseParams(ECR_Block);
		DrawDebugLine(
			GetWorld(),
			LineStart,
			LineEnd,
			FColor (255,0,0),
			false,
			-1.f,
			0,
			1.f
		);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECollisionChannel::ECC_Visibility, TraceParams, ResponseParams))
		{
			OutHitLocation = LineStart + ActorRot.Vector() * HitResult.Distance;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *OutHitLocation.ToString())
			return true;
		}
		else return false;
		
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