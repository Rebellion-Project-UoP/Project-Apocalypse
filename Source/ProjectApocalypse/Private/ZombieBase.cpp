// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"




// Sets default values
AZombieBase::AZombieBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.TickInterval = 1.0f;
	PrimaryActorTick.bCanEverTick = true;

	aggroRange = 2000.0f;

	_velocity = FVector::Zero();

	_behaviours = TArray<USteeringBehaviour*>();
}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();

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

	Move();

}

void AZombieBase::Move()
{
	FVector steeringForce = FVector::Zero();

	for (int i = 0; i < _behaviours.Num(); i++)
	{
		USteeringBehaviour* b = _behaviours[i];

		steeringForce += b->Calculate();

	}

	_velocity = steeringForce;

	

	_velocity.GetClampedToMaxSize(GetCharacterMovement()->MaxWalkSpeed);

	if (_velocity != FVector::Zero()) {
		_velocity.Z = 0;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("here"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, _velocity.ToString());

		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;

		//GetTransform().GetLocation() += _velocity * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		SetActorRotation(FMath::RInterpConstantTo(GetTransform().GetRotation().Rotator(), UKismetMathLibrary::Conv_VectorToRotator(_velocity), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 90)) ;

		/*velocity.y = 0;
		transform.position += velocity * Time.deltaTime;

		transform.forward = velocity.normalized;*/
	}

}







