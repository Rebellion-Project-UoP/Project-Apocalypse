// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "../ProjectApocalypseCharacter.h"
#include "Seek.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAPOCALYPSE_API USeek : public USteeringBehaviour
{
	GENERATED_BODY()
	
private:
	FVector _seekTargetPos;
	AProjectApocalypseCharacter* _playerRef;

public:
	// Sets default values for this component's properties
	USeek();

public:
	void BeginPlay() override;
	FVector Calculate() override;
};
