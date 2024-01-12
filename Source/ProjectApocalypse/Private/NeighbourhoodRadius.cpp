// Fill out your copyright notice in the Description page of Project Settings.


#include "NeighbourhoodRadius.h"
#include "ZombieBase.h"

// Sets default values for this component's properties
UNeighbourhoodRadius::UNeighbourhoodRadius()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	neighbours = TArray<AActor*>();
}


// Called when the game starts
void UNeighbourhoodRadius::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle UnusedHandle;

	GetOwner()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UNeighbourhoodRadius::UpdateNeighboursList, 0.5, true, 0);
}


// Called every frame
void UNeighbourhoodRadius::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNeighbourhoodRadius::UpdateNeighboursList()
{
	neighbours.Empty();

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetOwner()->GetActorLocation(), radius, TArray<TEnumAsByte<EObjectTypeQuery>>(), AZombieBase::StaticClass(), TArray<AActor*>() = { GetOwner() }, neighbours);

	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Red, FString::FormatAsNumber(neighbours.Num()));

}

