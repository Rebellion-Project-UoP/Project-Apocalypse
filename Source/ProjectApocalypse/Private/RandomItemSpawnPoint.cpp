// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomItemSpawnPoint.h"

// Sets default values
ARandomItemSpawnPoint::ARandomItemSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomItemSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	//for (int i = 0; i < numOfEmptyItemSpawn; i++)
	//{
	//	itemToSpawn.AddZeroed();
	//}
	
	SpawnItem();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
	//UE_LOG(LogTemp, Warning, TEXT("%i"), itemToSpawn.Num());
}

// Called every frame
void ARandomItemSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARandomItemSpawnPoint::SpawnItem()
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	//GetWorld()->SpawnActor<AActor>(itemToSpawn[FMath::RandRange(0, itemToSpawn.Max)], GetActorTransform(), spawnInfo);
}

//when choosing the random item to spawn, it should be relevant to the environment around it. Examples: next to an ammo/gun crate spawn weapons/ammo or next to a rubbish pile spawn trashy items or building materials.
