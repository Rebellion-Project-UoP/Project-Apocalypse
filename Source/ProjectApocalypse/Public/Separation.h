// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "ZombieBase.h"
#include "NeighbourhoodRadius.h"
#include "Components/CapsuleComponent.h"
#include "Separation.generated.h"

UCLASS()
class PROJECTAPOCALYPSE_API USeparation : public USteeringBehaviour
{
	GENERATED_BODY()

public:
	AZombieBase* parent;
	
public:
	void BeginPlay() override;
	FVector Calculate() override;
};
