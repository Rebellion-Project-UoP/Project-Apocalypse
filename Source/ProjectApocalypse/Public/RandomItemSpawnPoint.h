// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

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
	AActor* spawnedActor;

	UPROPERTY(EditAnywhere, Category = "Item Spawning")
	float delayTimer;

	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* CollisionBox;

	FActorSpawnParameters spawnInfo;

	FTimerHandle RespawnItemDelayTimerHandle;
	FTimerDelegate TimerDelegate;

	void SpawnItem();

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
