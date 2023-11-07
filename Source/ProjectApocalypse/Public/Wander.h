// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "Wander.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAPOCALYPSE_API UWander : public USteeringBehaviour
{
	GENERATED_BODY()


public:
	
public:
	FVector Calculate() override;

};
