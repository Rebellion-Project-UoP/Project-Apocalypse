// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"

#include "RandomItemSpawnPoint.generated.h"

UCLASS()
class PROJECTAPOCALYPSE_API ARandomItemSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomItemSpawnPoint();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Item Spawning")
	TArray<TSubclassOf<class AActor>> itemToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Item Spawning")
	TSubclassOf<class AActor> spawnedActor;

	UPROPERTY(VisibleAnywhere, Category = "Item Spawning")
	UClass* spawnedActorsClass;

	UPROPERTY(VisibleAnywhere, Category = "Item Spawning")
	bool bItemPickedUp = false;

	UFUNCTION()
	void SpawnItem();
};
