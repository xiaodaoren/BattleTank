// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelSpeed)
{
	auto ElevationChange = FMath::Clamp(RelSpeed, -1.f, 1.f) * MaxDegPerSec* GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinElevationDeg, MaxElevationDeg), 0, 0));
}


