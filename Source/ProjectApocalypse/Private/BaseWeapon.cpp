// Fill out your copyright notice in the Description page of Project Settings.

#define BulletTrace ECC_GameTraceChannel1

#include "BaseWeapon.h"
#include "ZombieBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "CollisionQueryParams.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


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

	BarrelSkeletalMesh = NewObject<USkeletalMesh>();
	GripSkeletalMesh = NewObject<USkeletalMesh>();
	MagazineSkeletalMesh = NewObject<USkeletalMesh>();
	StockSkeletalMesh = NewObject<USkeletalMesh>();
	ScopeSkeletalMesh = NewObject<USkeletalMesh>();

	BarrelExtensionStaticMesh = NewObject<UStaticMesh>();
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	UpdateWeaponMesh();
}

void ABaseWeapon::LineTrace()
{
	UWorld* World = GetWorld();

	// Set the collision channel to use for the line trace
	ECollisionChannel TraceChannel = ECollisionChannel::BulletTrace;
	//ECollisionChannel::ECC_PhysicsBody

	FCollisionQueryParams TraceParams;

	TraceParams.bReturnPhysicalMaterial = true;

	TArray<UCameraComponent*> FollowCamera;
	GetParentActor()->GetComponents<UCameraComponent>(FollowCamera);
	
	FVector StartPoint = GetParentActor()->GetActorLocation(); //needs to be changed to barrel socket
	FVector EndPoint = LineTrace(FollowCamera[0]->GetComponentLocation(), FollowCamera[0]->GetComponentLocation() + FollowCamera[0]->GetForwardVector()*5000); // change 5000 to the range variable
	
	FHitResult HitResult;

	bool bHit = World->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, TraceChannel, TraceParams);

	DrawDebugLine(World,StartPoint, EndPoint , FColor::Red, false, 2.0f, 0, 1.0f);


	if (bHit)
	{
		if (Cast<AZombieBase>(HitResult.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit a zombie!"));
			AZombieBase* Hit = Cast<AZombieBase>(HitResult.GetActor());


			if (HitResult.PhysMaterial.IsValid())
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, HitResult.GetActor()->GetName());
				
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, HitResult.PhysMaterial.Get()->GetName());
				
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Material: %s"), HitResult.PhysMaterial.Get()->SurfaceType));


				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hit physcis material!"));			
			}

			Hit->Destroy(); //temporary needs to have a damage function implimented.
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit a something!"));

		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit nothing!"));
}

FVector ABaseWeapon::LineTrace(FVector startPoint, FVector endPoint)
{
	UWorld* World = GetWorld();

	// Set the collision channel to use for the line trace
	ECollisionChannel TraceChannel = ECC_Visibility;
	
	FHitResult HitResult;

	bool bHit = World->LineTraceSingleByChannel(HitResult, startPoint, endPoint, TraceChannel);

	DrawDebugLine(World,startPoint, endPoint, FColor::Green, false, 2.0f, 0, 1.0f);

	if (bHit)
	{
		return HitResult.Location;
	}
	
	return endPoint;
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UpdateWeaponMesh();
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

	for (int i = 0; i < pellets; ++i)
	{
		LineTrace();
	}
}

void ABaseWeapon::Reload()
{
	UE_LOG(LogTemp,Warning,TEXT("RELOOOOOOOODING!"));

}

//int32 ABaseWeapon::CalculateScore(const FHitResult& HitResult)
//{
//	if (HitResult.BoneName == TEXT(""))
//		
//	return int32();
//}

void ABaseWeapon::OnInteractionCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComponent, int32 OtherBodytypeIndex,
                                              bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProjectApocalypseCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("The player"));
		// Destroy();
		// return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Not the player"));
}
