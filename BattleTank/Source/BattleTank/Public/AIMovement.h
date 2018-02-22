// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "AIMovement.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UAIMovement : public USplineComponent
{
	GENERATED_BODY()
public:
	void MoveAlongSpline();
	
private:
	UPROPERTY(EditAnywhere)
		float MovementSpeed = 5;
	int32 Time;
};
