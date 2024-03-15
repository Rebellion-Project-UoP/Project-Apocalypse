// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "ItemBaseClass.generated.h"

class AProjectApocalypseCharacter;

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

	virtual void PickUpAction(AProjectApocalypseCharacter* player);

	UFUNCTION(BlueprintCallable)
	virtual void UseAction(AProjectApocalypseCharacter* player);
};
