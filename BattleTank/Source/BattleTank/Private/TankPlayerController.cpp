// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"

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
		
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
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
		LineTrace(OutHitLocation, LookDirection);
		return true;
	}
	OutHitLocation = FVector(1.0);
	return false;
}

bool ATankPlayerController::LineTrace(FVector &HitLocation, FVector &LookDirection) const
{
	FHitResult HitResult;
	FVector LineStart;
	FRotator ActorRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(LineStart, ActorRot);
	FVector LineEnd = LineStart + LookDirection * LineTraceRange;
	//FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	//FCollisionResponseParams ResponseParams(ECR_Block);
	//DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor (255,0,0), false, -1.f, 0, 1.f); 
	if (GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECollisionChannel::ECC_Visibility))  //, TraceParams, ResponseParams)) trace and response params optional
	{
		//OutHitLocation = LineStart + ActorRot.Vector() * HitResult.Distance;
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; //discarded later
	return DeprojectScreenPositionToWorld(ScreenLocation[0], ScreenLocation[1], WorldLocation, LookDirection);
}