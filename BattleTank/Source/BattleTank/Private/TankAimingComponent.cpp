// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelRef(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;
	FVector OutLaunchVelocity;
	FVector StartPos = Barrel->GetSocketLocation(FName("Projectile"));
	//SuggestProjectileVelocity gets aim direction for barrel through OUT parameter OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartPos, HitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("firing at %s"), *AimDirection.ToString())
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDir)
{
	auto BarrelRot = Barrel->GetForwardVector().Rotation();
	auto AimRot = AimDir.Rotation();
	auto DeltaRot = AimRot - BarrelRot;
	Barrel->Elevate(5); //TODO remove magic number
}
