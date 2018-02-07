// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	ATank* GetControlledTank() const;
	ATank* ControlledTank = nullptr;
	void AimTowardsCrosshair(); //barrel movement
	bool GetHitLocation(FVector &OutHitLocation) const; //use reference for OUT parameters
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	UPROPERTY(EditAnywhere)
		float CrosshairXPos = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYPos = 0.33333;
};


