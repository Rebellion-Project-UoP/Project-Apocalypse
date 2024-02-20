// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "ZombieBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectApocalypse/ProjectApocalypseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "CollisionQueryParams.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include <Kismet/GameplayStatics.h>
#include "Math/UnitConversion.h"

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

	GripSkeletalMesh = NewObject<USkeletalMesh>();

	WeaponMagazine = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Magazine"));
	WeaponMagazine->SetupAttachment(WeaponBody);

	MagazineSkeletalMesh = NewObject<USkeletalMesh>();

	WeaponStock = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Stock"));
	WeaponStock->SetupAttachment(WeaponBody);

	StockSkeletalMesh = NewObject<USkeletalMesh>();

	WeaponScope = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Scope"));
	WeaponScope->SetupAttachment(WeaponBody);

	ScopeSkeletalMesh = NewObject<USkeletalMesh>();

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

	WorldRef = GetWorld();
	
	Mag = 0;

	ReloadTime = 0;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<AProjectApocalypseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Mag = MagSize;

	UpdateWeaponMesh();
}

void ABaseWeapon::LineTrace()
{
	// Set the collision channel to use for the line trace
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility;

	FCollisionQueryParams TraceParams;

	TraceParams.bReturnPhysicalMaterial = true;

	TArray<UCameraComponent*> FollowCamera;
	GetParentActor()->GetComponents<UCameraComponent>(FollowCamera);

	FVector StartPoint = GetParentActor()->GetActorLocation(); //needs to be changed to barrel socket

	FVector HitLocation = LineTrace(FollowCamera[0]->GetComponentLocation(), FollowCamera[0]->GetComponentLocation() + FollowCamera[0]->GetForwardVector()*5000); // change 5000 to the range variable

	FVector Direction = HitLocation - StartPoint;
	
	FVector EndPoint = StartPoint + Direction.GetSafeNormal()*5000; //temporary until designer begins implementing weapon stats then use range

	//FVector EndPoint = Direction.GetSafeNormal()*Range;

	FHitResult HitResult;

	bool bHit = WorldRef->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, TraceChannel, TraceParams);

	DrawDebugLine(WorldRef,StartPoint, EndPoint , FColor::Red, false, 2.0f, 0, 1.0f);


	if (bHit)
	{
		if (Cast<AZombieBase>(HitResult.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit a zombie!"));
			AZombieBase* Hit = Cast<AZombieBase>(HitResult.GetActor());
			
			DealDamage(Hit);

			if (!IsValid(Hit))
			{
				if (HitResult.PhysMaterial.IsValid())
				{
					PlayerRef->PlayerScore += CalculateScore(HitResult);
				}

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Works"));
			} // Remember to fix this so that it takes score only when the player final shot hits. 
			  //Ask Niamh if hit markers with score is okay as it will fix this problem and could have a chunk of score like 50 when the zombie is killed.

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Score: %i"), PlayerRef->PlayerScore));

			//Hit->Destroy(); //temporary needs to have a damage function implimented.

			return;
		}

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, UEnum::GetValueAsString(TraceChannel));

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, HitResult.GetActor()->GetName());

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit a something!"));

		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit nothing!"));
}

FVector ABaseWeapon::LineTrace(FVector startPoint, FVector endPoint)
{
	// Set the collision channel to use for the line trace
	ECollisionChannel TraceChannel = ECC_Visibility;
	
	FHitResult HitResult;

	bool bHit = WorldRef->LineTraceSingleByChannel(HitResult, startPoint, endPoint, TraceChannel);

	//DrawDebugLine(WorldRef,startPoint, endPoint, FColor::Green, false, 2.0f, 0, 1.0f);

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
	if (Mag > 0)
	{
		for (int i = 0; i < pellets; ++i)
		{
			LineTrace();
		}
		
		--Mag;
		
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Click Click... No ammo!?"));
}

void ABaseWeapon::Reload()
{
	//needs to be changed to actual reload time from weapons stat
	// if (!ReloadTime>0.0f)
	// {
	// 	ReloadTime = 3.0f;
	// } //safety net to stop reloading being re-triggered.

	if (Ammunition > 0)
	{
		ReloadTime = 3.0f;

		//GetWorldTimerManager().SetTimer(ReloadTimer, this, Reloading, 1.0f, true, 2.0f);
		GetWorldTimerManager().SetTimer(ReloadingTimer, this, &ABaseWeapon::Reloading, 0.1f, true);
		//

		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No reserve ammo"));
}

void ABaseWeapon::Reloading()
{
	ReloadTime -= 0.1f;
	
	//UE_LOG(LogTemp,Warning,TEXT("RELOOOOOOOODING!"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("RELOOOOOOOODING!"));

	
	if (ReloadTime <=0)
	{
		//some logic to detect remaining ammo supply and apply based on remaining suply or magsize.
		//additionally need to remove reloaded amount from supply.
		
		Mag = MagSize;

		//UE_LOG(LogTemp,Warning,TEXT("%i"), Mag);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("%i"), Mag);

		// setting ammunition and checking to see if its less than 0;
		if ((Ammunition -= MagSize)<1)
		{
			Ammunition = 0;
		}
		
		//UE_LOG(LogTemp,Warning,TEXT("RELOADED!!"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("RELOADED!!"));

		
		GetWorldTimerManager().ClearTimer(ReloadingTimer); //stopping the timer as reloading has been finished.
	}
}

int32 ABaseWeapon::CalculateScore(const FHitResult& HitResult)
{	
	int32 score = 0;
	
	if (HitResult.PhysMaterial->SurfaceType == SurfaceType1)
	{		
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Head"));
		score = 20;
	}
	else if (HitResult.PhysMaterial->SurfaceType == SurfaceType2)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Torso"));
		score = 10;
	}
	else if (HitResult.PhysMaterial->SurfaceType == SurfaceType3)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Limb"));
		score = 5;
	}
		
	return score;
}

void ABaseWeapon::DealDamage(AZombieBase* Zombie)
{
	UHealthComp* ZombieHealthComp = Cast<UHealthComp>(Zombie->GetComponentByClass(UHealthComp::StaticClass()));

	if (ZombieHealthComp)
	{
		IDamageInterface::Execute_TakeDamage(ZombieHealthComp, 100);   //Change 100 to Damage variable
	}
}

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

