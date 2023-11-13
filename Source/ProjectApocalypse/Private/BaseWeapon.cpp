// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	WeaponBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponBody"));
	WeaponBody->SetupAttachment(Root);

	WeaponBarrel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Barrel"));
	WeaponBarrel->SetupAttachment(WeaponBody);

	WeaponBarrelExtension = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ldaigf"));
	WeaponBarrelExtension->SetupAttachment(WeaponBody);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponBody->SetSkeletalMeshAsset(WeaponBodySkeletalMesh);

	WeaponBarrel->SetSkeletalMeshAsset(BarrelSkeletalMesh);

	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}