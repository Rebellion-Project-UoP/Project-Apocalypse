// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NeighbourhoodRadius.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTAPOCALYPSE_API UNeighbourhoodRadius : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AActor*> neighbours;

	float radius = 500;

public:	
	// Sets default values for this component's properties
	UNeighbourhoodRadius();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateNeighboursList();
};
