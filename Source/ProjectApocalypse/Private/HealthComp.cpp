// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComp.h"
#include "ZombieBase.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();
	currHealth = maxHealth;
	// ...
	
}


// Called every frame
void UHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UHealthComp::TakeDamage_Implementation(float damage)
{
	currHealth -= damage;

	if (currHealth > 0) {
		
		return;
	}

	AZombieBase* zombie = Cast<AZombieBase>(GetOwner());

	if (zombie) {
		zombie->Death();
		return;
	}

	GetOwner()->Destroy();
}

