// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) //Makes class accessible by BP
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegPerSec = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDeg = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDeg = 0;
};
