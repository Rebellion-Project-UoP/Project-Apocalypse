// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	WeaponBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponBody"));
	WeaponBody->SetupAttachment(Root);

	WeaponBarrel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Barrel"));
	WeaponBarrel->SetupAttachment(WeaponBody);

	WeaponBarrelExtension = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Extension"));
	WeaponBarrelExtension->SetupAttachment(WeaponBody);

	WeaponGrip = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Grip"));
	WeaponGrip->SetupAttachment(WeaponBody);

	WeaponMagazine = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Magazine"));
	WeaponMagazine->SetupAttachment(WeaponBody);

	WeaponStock = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Stock"));
	WeaponStock->SetupAttachment(WeaponBody);

	WeaponScope = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Scope"));
	WeaponScope->SetupAttachment(WeaponBody);

	InteractionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Interaction Capsule"));
	InteractionCapsule->SetupAttachment(Root);

	InteractionCapsule->OnComponentBeginOverlap.AddDynamic(this,&ABaseWeapon::OnInteractionCapsuleOverlap);

	WeaponBarrelExtension->SetWorldLocation(WeaponBarrel->GetSocketLocation(TEXT("BarrelEndSocket")));
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	UpdateWeaponMesh();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateWeaponMesh();
}

void ABaseWeapon::UpdateWeaponMesh()
{
	WeaponBody->SetMaterial(0, WeaponSkin);
	WeaponBarrel->SetMaterial(0, WeaponSkin);
	WeaponBarrelExtension->SetMaterial(0, WeaponSkin);
	WeaponGrip->SetMaterial(0, WeaponSkin);
	WeaponMagazine->SetMaterial(0, WeaponSkin);
	WeaponStock->SetMaterial(0, WeaponSkin);
	WeaponScope->SetMaterial(0, WeaponSkin);
	
	WeaponBarrel->SetSkeletalMeshAsset(BarrelSkeletalMesh);

	WeaponGrip->SetSkeletalMeshAsset(GripSkeletalMesh);

	WeaponMagazine->SetSkeletalMeshAsset(MagazineSkeletalMesh);

	WeaponStock->SetSkeletalMeshAsset(StockSkeletalMesh);

	WeaponScope->SetSkeletalMeshAsset(ScopeSkeletalMesh);
	
	
	if (BarrelSkeletalMesh)
	{
		WeaponBarrelExtension->SetWorldLocation(WeaponBarrel->GetSocketLocation(TEXT("BarrelEndSocket")));

		WeaponBarrelExtension->SetStaticMesh(BarrelExtensionStaticMesh);

		return;
	}
	
	BarrelExtensionStaticMesh = nullptr;

	WeaponBarrelExtension->SetStaticMesh(nullptr);
}

void ABaseWeapon::FireWeapon()
{
	UE_LOG(LogTemp,Warning,TEXT("BANG! BANG!"));
}

void ABaseWeapon::OnInteractionCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodytypeIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProjectApocalypseCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("The player"));
		// Destroy();
		// return;
	}

	UE_LOG(LogTemp, Warning, TEXT("not player"));
}