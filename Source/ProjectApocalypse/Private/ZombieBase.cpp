// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"
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

	swipeHitBox = Cast<UBoxComponent>(GetComponentsByTag(UBoxComponent::StaticClass(), "attack")[0]);

	swipeHitBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true), "rh_attackHitBox");

	swipeHitBox->OnComponentBeginOverlap.AddDynamic(this, &AZombieBase::OnBoxBeginOverlap);

	neighbourhood = GetComponentByClass<UNeighbourhoodRadius>();
	
	healthComponent = Cast<UHealthComp>(GetComponentByClass(UHealthComp::StaticClass()));
	
	//gets the behaviours attached to the zombie
	TArray<UActorComponent*> behavioursFound = GetComponentsByClass(USteeringBehaviour::StaticClass());

	for(int i = 0; i < behavioursFound.Num(); i++ )
	{
		USteeringBehaviour* b = Cast<USteeringBehaviour>(behavioursFound[i]);
		_behaviours.Add(b);
		
	};
	
	//FTimerHandle UnusedHandle;
	//GetWorldTimerManager().SetTimer(UnusedHandle, this, &AZombieBase::MoveToPlayer, 2, true, 0);

	
	//_skeletalMesh = Cast<USkeletalMeshComponent>(this->GetComponentByClass(USkeletalMeshComponent::StaticClass));

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
}




// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!playerDetected) {

		SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(GetActorRotation(), _velocity.ToOrientationRotator(), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 80));
	



		Move();
	}


}

void AZombieBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProjectApocalypseCharacter>(OtherActor)) {
		AProjectApocalypseCharacter* player = Cast<AProjectApocalypseCharacter>(OtherActor);

		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Red, "damage");

		if (Cast<UHealthComp>(player->GetComponentByClass(UHealthComp::StaticClass()))->Implements<UDamageInterface>()) {
			UHealthComp* health = Cast<UHealthComp>(player->GetComponentByClass(UHealthComp::StaticClass()));

			IDamageInterface::Execute_TakeDamage(health, 20);
		}
	}
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
	

	_velocity.GetClampedToSize(0,GetCharacterMovement()->MaxWalkSpeed);

	if (_velocity != FVector::Zero()) {
		_velocity.Z = 0;

		GetMovementComponent()->AddInputVector((GetActorForwardVector()));

	}

}







