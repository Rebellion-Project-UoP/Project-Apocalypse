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

	BulletDirection = FVector(0,0,0);
	
	Mag = 0;

	ReloadTime = 0;

	Magnification = 2;

	HeadshotMultiplier = 1.5f;
	BodyShotMultiplier = 1.0f;
	LimbShotMultiplier = 0.75f;
	FireRateCounter = 0;
	
	bCanFire = true;

	IsReloading = false;

	bMakeEmptyNoise = false;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<AProjectApocalypseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Mag = MagSize;

	UpdateWeaponMesh();

	TrueAccuracy = FMath::Lerp(0.05F, 0.0F, Accuracy/100);
}

FHitResult ABaseWeapon::LineTrace()
{
	// Set the collision channel to use for the line trace
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility;

	FCollisionQueryParams TraceParams;

	TraceParams.bReturnPhysicalMaterial = true;

	TArray<UCameraComponent*> FollowCamera;
	GetParentActor()->GetComponents<UCameraComponent>(FollowCamera);

	//FVector StartPoint = GetParentActor()->GetActorLocation(); //needs to be changed to barrel socket
	FVector StartPoint = WeaponBarrel->GetSocketLocation("BarrelExtension-Slot");

	FVector HitLocation = LineTrace(FollowCamera[0]->GetComponentLocation(), FollowCamera[0]->GetComponentLocation() + FollowCamera[0]->GetForwardVector()*5000); // change 5000 to the range variable

	FVector Direction = HitLocation - StartPoint;

	Direction = Direction.GetSafeNormal() + FVector3d(FMath::RandRange(-TrueAccuracy,TrueAccuracy),FMath::RandRange(-TrueAccuracy,TrueAccuracy),FMath::RandRange(-TrueAccuracy,TrueAccuracy));

	BulletDirection = Direction;
	
	FVector EndPoint = StartPoint + Direction*Range; //temporary until designer begins implementing weapon stats then use range

	//FVector EndPoint = Direction.GetSafeNormal()*Range;

	FHitResult HitResult;

	bool bHit = WorldRef->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, TraceChannel, TraceParams);

	//DrawDebugLine(WorldRef,StartPoint, EndPoint , FColor::Red, false, 2.0f, 0, 1.0f);

	if (bHit)
	{
		if (Cast<AZombieBase>(HitResult.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit a zombie!"));
			AZombieBase* Hit = Cast<AZombieBase>(HitResult.GetActor());

			DealDamage(Hit, HitResult);

			if (Hit->healthComponent->currHealth <= 0 && Hit->hasPointsBeenReceived == false)
			{
				if (HitResult.PhysMaterial.IsValid())
				{
					PlayerRef->PlayerScore += CalculateScore(HitResult);

					Hit->hasPointsBeenReceived = true;
				}

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Works"));
			}
			
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Score: %i"), PlayerRef->PlayerScore));

			return HitResult;
		}

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit a something!"));

		return HitResult;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You hit nothing!"));
	return HitResult;

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

void ABaseWeapon::FireRateCooldown()
{
	FireRateCounter += 0.025f;

	if (FireRateCounter >= FireRate)
	{
		EndFireWeapon();
		
		FireRateCounter = 0;
		
		GetWorldTimerManager().ClearTimer(FireRateTimer); //stopping the timer as fire rate cooldown has been finished.
	}
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

FHitResult ABaseWeapon::FireWeapon()
{
	FHitResult result;
	
	if (Mag > 0)
	{
		switch (FireMode)
		{
		case 0: // Single Fire
			result = SingleFire();
			break;
		case 1: // Burst Fire
			result = BurstFire();
			break;
		case 2: // Auto Fire
			result = AutoFire();
			break;
		}

		bCanFire = false;

		bIsFiring = true;

		GetWorldTimerManager().SetTimer(FireRateTimer, this, &ABaseWeapon::FireRateCooldown, 0.025f, true);

		return result;
	}

	if (bIsFiring||Ammunition<1)
	{
		if (bMakeEmptyNoise)
		{
			UGameplayStatics::PlaySound2D(this, MagEmptyNoise);
			
			bMakeEmptyNoise = false;
		}

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Can't fire weapon"));

		return result;
	}

	Reload();
	
	return result;
}

void ABaseWeapon::EndFireWeapon()
{
	if (!IsReloading)
	{
		bCanFire = true;
	}
}

void ABaseWeapon::Reload()
{
	if (Ammunition > 0 && Mag!=MagSize && !IsReloading)
	{
		bCanFire = false;

		IsReloading = true;

		UGameplayStatics::PlaySound2D(this, ReloadNoise);
		
		ReloadTime = ReloadSpeed;
		
		GetWorldTimerManager().SetTimer(ReloadingTimer, this, &ABaseWeapon::Reloading, 0.1f, true);

		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No reserve ammo"));
}

void ABaseWeapon::Reloading()
{
	ReloadTime -= 0.1f;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Reloading in: %f"),ReloadTime));

	
	if (ReloadTime <=0)
	{		
		int SpentAmmo = MagSize-Mag; //calc spent ammo

		if (Ammunition<SpentAmmo)
		{
			Mag += Ammunition;
		}
		else
		{
			Mag += SpentAmmo;
		}
		
		Ammunition -= SpentAmmo;
		
		if (Ammunition <1) //minus spent ammo to reserves
		{
			Ammunition = 0;
		}
		
		GetWorldTimerManager().ClearTimer(ReloadingTimer); //stopping the timer as reloading has been finished.

		bCanFire = true;
		
		IsReloading = false;
	}
}

FHitResult ABaseWeapon::SingleFire()
{
	FHitResult result;

	UGameplayStatics::PlaySound2D(this, GunShotNoise);
	
	for (int i = 0; i < pellets; ++i)
	{
		result = LineTrace();
	}
	
	--Mag;

	bCanFire = false;
	
	return result;
}

FHitResult ABaseWeapon::BurstFire()
{	
	FHitResult result;
	
	UGameplayStatics::PlaySound2D(this, GunShotNoise);
	
	for (int i = 0; i < pellets; ++i)
	{
		result = LineTrace();
	}
	
	--Mag;
	
	return result;
	
}

FHitResult ABaseWeapon::AutoFire()
{
	FHitResult result;

	UGameplayStatics::PlaySound2D(this, GunShotNoise);
	
	for (int i = 0; i < pellets; ++i)
	{
		result = LineTrace();
	}
	
	--Mag;

	return result;
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

void ABaseWeapon::DealDamage(AZombieBase* Zombie, const FHitResult& HitResult)
{
	UHealthComp* ZombieHealthComp = Cast<UHealthComp>(Zombie->GetComponentByClass(UHealthComp::StaticClass()));

	float finalDamage = 0;

	if (ZombieHealthComp)
	{
		if (HitResult.PhysMaterial->SurfaceType == SurfaceType1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Head"));

			finalDamage = Damage * HeadshotMultiplier;
		}
		else if (HitResult.PhysMaterial->SurfaceType == SurfaceType2)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Torso"));

			finalDamage = Damage * BodyShotMultiplier;
		}
		else if (HitResult.PhysMaterial->SurfaceType == SurfaceType3)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Limb"));

			finalDamage = Damage * LimbShotMultiplier;
		}

		IDamageInterface::Execute_TakeDamage(ZombieHealthComp, finalDamage);   //Change 100 to Damage variable
		Zombie->Flinch();

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Damage: %f"), finalDamage));
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
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Not the player"));
}

