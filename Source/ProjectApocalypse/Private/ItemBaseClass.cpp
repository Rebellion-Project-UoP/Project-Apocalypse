// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBaseClass.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"

// Sets default values
AItemBaseClass::AItemBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(Root);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AItemBaseClass::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AItemBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
	//_myPlayerRef = Cast<AProjectApocalypseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AItemBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBaseClass::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, 
AActor *OtherActor, 
UPrimitiveComponent *OtherComponent, 
int32 OtherBodyIndex, 
bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<AProjectApocalypseCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Collided with the Player!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Collided not with the Player!"));
	}
}
