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

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _wanderRadius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _wanderDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _wanderJitter;

private:
	FVector _wanderTarget;
	float _wanderAngle;

public:
	UWander();
	void BeginPlay() override;
	
public:
	FVector Calculate() override;

private:
	void UpdateAngle();
};
