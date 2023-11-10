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
	radius = 200.0f;
}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();

	_aiController = Cast<AAIController>(GetController());
	
	FTimerHandle UnusedHandle;

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AZombieBase::Move, 4, true, 0);
	
}


void AZombieBase::Move()
{
	FNavLocation result;

	UNavigationSystemV1* navData = UNavigationSystemV1::GetCurrent(GetWorld());
	navData->GetRandomReachablePointInRadius(GetActorLocation() , radius, result);
	
	_aiController->MoveToLocation(result.Location, (-1.0f), false);

	//_aiController->MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	
	
	


}


// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void AZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




