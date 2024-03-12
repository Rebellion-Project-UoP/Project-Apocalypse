// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomItemSpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"
#include <ItemBaseClass.h>

// Sets default values
ARandomItemSpawnPoint::ARandomItemSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(Root);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARandomItemSpawnPoint::OnOverlapBegin);

	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	delayTimer = 3;
}

// Called when the game starts or when spawned
void ARandomItemSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnItem();

	//TimerDelegate.BindUFunction(this, FName("SpawnItem"));
}

// Called every frame
void ARandomItemSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARandomItemSpawnPoint::SpawnItem()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Spawn!"));

	GetWorldTimerManager().ClearTimer(RespawnItemDelayTimerHandle);
	
	int randNumber = FMath::RandRange(0, (itemToSpawn.Num() - 1));

	if (itemToSpawn[randNumber])
	{
		spawnedActor = GetWorld()->SpawnActor<AActor>(itemToSpawn[randNumber], GetActorTransform(), spawnInfo);

		return;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Not Valid Actor to Spawn"));
		
		spawnedActor = nullptr;

		GetWorldTimerManager().SetTimer(RespawnItemDelayTimerHandle, this, &ARandomItemSpawnPoint::SpawnItem, delayTimer, false);

		return;
	}
}

void ARandomItemSpawnPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Collided with the player!"));

	if (spawnedActor && OtherActor != spawnedActor)
	{
		AProjectApocalypseCharacter* player = Cast<AProjectApocalypseCharacter>(OtherActor);

		if (player)
		{
			AItemBaseClass* itemBaseClassRef = Cast<AItemBaseClass>(spawnedActor);

			if (itemBaseClassRef)
			{
				itemBaseClassRef->PickUpAction(player);

				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Item picked up!"));

				spawnedActor->Destroy();

				spawnedActor = nullptr;

				GetWorldTimerManager().SetTimer(RespawnItemDelayTimerHandle, this, &ARandomItemSpawnPoint::SpawnItem, delayTimer, false);
			}
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Collided not with the player!"));
		}

	}

}

//when choosing the random item to spawn, it should be relevant to the environment around it. 
//Examples: next to an ammo/gun crate spawn weapons/ammo or next to a rubbish pile spawn trashy items or building materials.

