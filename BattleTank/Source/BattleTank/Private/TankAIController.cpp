// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is seen by %s"), *PlayerTank->GetName(),*ControlledTank->GetName())
	}
	else UE_LOG(LogTemp, Error, TEXT("Player is not seen"))
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

}

void ATankAIController::AimTowardsPlayer()
{
	ATank* PlayerTank = GetPlayerTank();
	if (!GetControlledTank()) return;
	if (PlayerTank)
	{
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());
	}
}


