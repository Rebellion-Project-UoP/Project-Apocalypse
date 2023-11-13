// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Wander.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTAPOCALYPSE_API UWander : public USteeringBehaviour
{
	GENERATED_BODY()

private:
	ANavMeshBoundsVolume* navMesh;

public:
	void BeginPlay() override;
	
public:
	FVector Calculate() override;

};
