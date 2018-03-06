// Fill out your copyright notice in the Description page of Project Settings.

#include "AIMovement.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameState.h"

//get current location on spline
//find next point on spline
//calculate new position with movement speed, current position and spline direction
//calculate new rotation with spline rotation
//set new position and rotation

void UAIMovement::MoveAlongSpline()
{
	Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	Time = fmod(Time, Duration);
	
	Distance = Distance + MovementSpeed;
	auto CurrentPos = GetOwner()->GetActorLocation();
	//auto DesiredPos = GetLocationAtDistanceAlongSpline(GetDistanceAlongSplineAtSplinePoint(SplineIndex), ESplineCoordinateSpace::World);
	auto SplineDir = FindDirectionClosestToWorldLocation(CurrentPos, ESplineCoordinateSpace::World);
	//auto SplineDir = GetWorldDirectionAtTime(Time, true); 
	//auto SplineDir = GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	SplineDir.Z = GetOwner()->GetActorForwardVector().Z; //overwrite Z with tank's forward vector
	auto SplineRot = FindRotationClosestToWorldLocation(CurrentPos, ESplineCoordinateSpace::World);
	//auto SplineRot = GetRotationAtTime(Time, ESplineCoordinateSpace::World);
	//auto SplineRot = GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	
	auto NewPos = CurrentPos + MovementSpeed * SplineDir;
	GetOwner()->SetActorLocation(NewPos);
	GetOwner()->SetActorRelativeRotation(SplineRot); 
	
	auto LineEnd = CurrentPos + SplineDir * 1000;
	DrawDebugLine(GetWorld(), CurrentPos, LineEnd, FColor(255, 0, 0), false, -1.f, 0, 50.f);
}

FVector UAIMovement::GetNextGoal()
{
	Distance = Distance + MovementSpeed;
	NextGoal = GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	//NextGoal.Z = GetOwner()->GetActorForwardVector().Z;

	auto CurrentPos = GetOwner()->GetActorLocation();
	DrawDebugLine(GetWorld(), CurrentPos, NextGoal, FColor(255, 0, 0), false, -1.f, 0, 50.f);

	return NextGoal;
}