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
	UE_LOG(LogTemp, Warning, TEXT("%d"), Time)
	auto CurrentPos = GetOwner()->GetActorLocation();
	//auto DesiredPos = GetLocationAtDistanceAlongSpline(GetDistanceAlongSplineAtSplinePoint(SplineIndex), ESplineCoordinateSpace::World);
	//auto SplineDir = FindDirectionClosestToWorldLocation(CurrentPos, ESplineCoordinateSpace::World);
	auto SplineDir = GetWorldDirectionAtTime(Time, true); 
	//auto SplineRot = FindRotationClosestToWorldLocation(CurrentPos, ESplineCoordinateSpace::World);
	auto SplineRot = GetRotationAtTime(Time, ESplineCoordinateSpace::World);
	auto NewPos = CurrentPos + MovementSpeed * SplineDir;// *Time;
	GetOwner()->SetActorLocation(NewPos);
	GetOwner()->SetActorRelativeRotation(SplineRot); // TODO relative?
	
	auto LineEnd = CurrentPos + SplineDir * 1000;
	DrawDebugLine(GetWorld(), CurrentPos, LineEnd, FColor(255, 0, 0), false, -1.f, 0, 50.f);
}