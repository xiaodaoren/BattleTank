// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

//Forward Declaration
class UTankBarrel; 

//Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelRef(UTankBarrel* BarrelToSet);
	
protected:

public:	
	void AimAt(FVector HitLocation, float LaunchSpeed);
	int frame = 0;
	
private: 
	UTankBarrel* Barrel = nullptr;
	void MoveBarrel(FVector AimDir);
};
