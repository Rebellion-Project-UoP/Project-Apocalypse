// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "SteeringBehaviour.h"
#include "ZombieController.h"
#include "GameFramework/Character.h"
#include "ZombieBase.generated.h"
UCLASS()
class PROJECTAPOCALYPSE_API AZombieBase : public ACharacter
{
	GENERATED_BODY()

public:
	//stores the zombies aggro range
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float aggroRange;

private:
	//stores the reference to the zombies ai controller
	AZombieController* _aiController;
	FVector _velocity;

	//stores all steering behaviours for the zombie
	TArray<USteeringBehaviour*> _behaviours;
public:
	// Sets default values for this character's properties
	AZombieBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();
	
};


//steering behaviours to add
//Wander
//Separation
//wall avoidance
//obstacle avoidance
//
