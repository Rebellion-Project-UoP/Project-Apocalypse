// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBaseClass.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"

// Sets default values
AItemBaseClass::AItemBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AItemBaseClass::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItemBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBaseClass::PickUpAction(AProjectApocalypseCharacter* player)
{

}

void AItemBaseClass::UseAction(AProjectApocalypseCharacter* player)
{

}



