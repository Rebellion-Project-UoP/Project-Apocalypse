// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
AZombieBase::AZombieBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	aggroRange = 2000.0f;

	_velocity = FVector(0);

	_behaviours = TArray<USteeringBehaviour*>();
}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();

	_aiController = Cast<AZombieController>(GetController());
	
	//gets the behaviours attached to the zombie
	//TArray<UActorComponent*> behavioursFound = GetComponentsByClass(USteeringBehaviour::StaticClass());

	//for(int i = 0; i < behavioursFound.Num(); i++ )
	//{
		//USteeringBehaviour* b = Cast<USteeringBehaviour>(behavioursFound[i]);
		//_behaviours.Add(b);
		
	//};
	
	//FTimerHandle UnusedHandle;
	//GetWorldTimerManager().SetTimer(UnusedHandle, this, &AZombieBase::MoveToPlayer, 2, true, 0);

	
	
}


// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AZombieBase::Move()
{
	FVector steeringForce = FVector(0);

	

}







