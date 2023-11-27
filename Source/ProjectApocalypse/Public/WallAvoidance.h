// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "WallAvoidance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAPOCALYPSE_API UWallAvoidance : public USteeringBehaviour
{
	GENERATED_BODY()
	

public:
		FVector Calculate() override;

};
