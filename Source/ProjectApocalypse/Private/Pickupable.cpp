// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickupable.h"

// Sets default values for this component's properties
UPickupable::UPickupable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &UPickupable::OnOverlapBegin);
}


// Called when the game starts
void UPickupable::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UPickupable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickupable::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, 
AActor *OtherActor, 
UPrimitiveComponent *OtherComponent, 
int32 OtherBodyIndex, 
bool bFromSweep, const FHitResult &SweepResult)
{

}
