// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

FVector AZombieBase::getSteeringVelocity()
{
	return _velocity;
}

// Sets default values
AZombieBase::AZombieBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;

	aggroRange = 2000.0f;

	_velocity = FVector::Zero();

	_behaviours = TArray<USteeringBehaviour*>();

	playerDetected = false;


}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();

	AddComponentByClass(UNeighbourhoodRadius::StaticClass(), false, this->GetActorTransform(), true);

	neighbourhood = GetComponentByClass<UNeighbourhoodRadius>();


	_aiController = Cast<AZombieController>(GetController());
	
	//gets the behaviours attached to the zombie
	TArray<UActorComponent*> behavioursFound = GetComponentsByClass(USteeringBehaviour::StaticClass());

	for(int i = 0; i < behavioursFound.Num(); i++ )
	{
		USteeringBehaviour* b = Cast<USteeringBehaviour>(behavioursFound[i]);
		_behaviours.Add(b);
		
	};
	
	//FTimerHandle UnusedHandle;
	//GetWorldTimerManager().SetTimer(UnusedHandle, this, &AZombieBase::MoveToPlayer, 2, true, 0);

	
	
}


// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!playerDetected) {

		SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(GetActorRotation(), _velocity.ToOrientationRotator(), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 80));
	



		Move();
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.1, FColor::Red, FString::SanitizeFloat(GetCharacterMovement()->Velocity.Length()));


}

void AZombieBase::Move()
{
	FVector steeringForce = FVector::Zero();

	for (int i = 0; i < _behaviours.Num(); i++)
	{
		USteeringBehaviour* b = _behaviours[i];

		steeringForce += b->Calculate();

	}

	FVector accel = steeringForce / 1;
	_velocity = accel * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	

	_velocity.GetClampedToSize(70,GetCharacterMovement()->MaxWalkSpeed);

	if (_velocity != FVector::Zero()) {
		_velocity.Z = 0;

		GetMovementComponent()->AddInputVector((GetActorForwardVector()));

	}

}







