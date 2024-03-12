// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "../ProjectApocalypseCharacter.h"
#include "Seek.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTAPOCALYPSE_API USeek : public USteeringBehaviour
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USeek();

public:
	void BeginPlay() override;
	FVector Calculate() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector seekTargetPos;
};
