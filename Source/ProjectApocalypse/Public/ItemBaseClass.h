// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include <RandomItemSpawnPoint.h>
#include "GameFramework/Actor.h"
#include "ItemBaseClass.generated.h"

UCLASS()
class PROJECTAPOCALYPSE_API AItemBaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* CollisionBox;	

	ARandomItemSpawnPoint* ItemSpawnerRef;

	//AProjectApocalypseCharacter* _myPlayerRef;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetItemSpawnPointRef(ARandomItemSpawnPoint* Ref);
};
