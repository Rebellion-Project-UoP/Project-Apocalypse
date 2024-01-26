// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomItemSpawnPoint.h"
#include "Kismet/GameplayStatics.h"

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
	
	SpawnItem();
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
	
	int randNumber = FMath::RandRange(0, (itemToSpawn.Max() - 1));

	GetWorld()->SpawnActor<AActor>(itemToSpawn[randNumber], GetActorTransform(), spawnInfo);

	spawnedActor = itemToSpawn[randNumber];

	if (spawnedActor != nullptr)
	{
		spawnedActorsClass = spawnedActor.Get();
		
		//spawnedActorsClass.
	}


	//Debug
		//UE_LOG(LogTemp, Warning, TEXT("%i"), randNumber);
		//UE_LOG(LogTemp, Warning, TEXT("%i"), itemToSpawn.Num());
		//GetWorld()->SpawnActor<AActor>(itemToSpawn[FMath::RandRange(0, (itemToSpawn.Max() - 1))], GetActorTransform(), spawnInfo);
		//GetWorld()->SpawnActor<AActor>(itemToSpawn[0], GetActorTransform(), spawnInfo);
}

//when choosing the random item to spawn, it should be relevant to the environment around it. Examples: next to an ammo/gun crate spawn weapons/ammo or next to a rubbish pile spawn trashy items or building materials.

//Add the feature of regenerating the random spawn after the item has been picked up. This will be done after I have completed working on the player pick up.

//Maybe check whether the spawned item variable becomes null because the item is interacted with then it can be respawned?
//But then need to get around the fact that the variable will be null when nothing is spawned
//However this could be good and be what the designer wants.