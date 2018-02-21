// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelRef(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) return;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretRef(UTankTurret * TurretToSet)
{
	if (!TurretToSet) return;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;
	FVector OutLaunchVelocity;
	FVector StartPos = Barrel->GetSocketLocation(FName("Projectile"));
	//SuggestProjectileVelocity gets aim direction for barrel through OUT parameter OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartPos, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDir)
{
	auto BarrelRot = Barrel->GetForwardVector().Rotation();
	auto AimRot = AimDir.Rotation();
	auto DeltaRot = AimRot - BarrelRot;
	Barrel->Elevate(DeltaRot.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDir)
{
	auto TurretRot = Turret->GetForwardVector().Rotation();
	auto AimRot = AimDir.Rotation();
	auto DeltaRot = AimRot - TurretRot;
	Turret->Rotate(DeltaRot.GetNormalized().Yaw);
}