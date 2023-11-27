// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "WallAvoidance.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTAPOCALYPSE_API UWallAvoidance : public USteeringBehaviour
{
	GENERATED_BODY()
	


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float viewDistance;
	


public:
		FVector Calculate() override;

};
