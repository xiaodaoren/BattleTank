// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelSpeed)
{
	auto RotationChange = FMath::Clamp(RelSpeed, -1.f, 1.f) * MaxDegPerSec * GetWorld()->DeltaTimeSeconds;
	auto RawNewRot = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewRot, 0));
}

