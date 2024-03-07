// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include <ZombieBase.h>
#include "../ProjectApocalypseCharacter.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "BaseWeapon.generated.h"

UENUM (BlueprintType)
enum class FiringMode: uint8
{	 SingleFire UMETA(DisplayName="Single"),
	 BurstFire UMETA(DisplayName="Burst"),
	 AutoFire UMETA(DisplayName="Auto")
};

UCLASS()
class PROJECTAPOCALYPSE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Ammo")
	int Ammunition;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Ammo")
	int MaxAmmunition;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Ammo")
	int MagSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Ammo")
	int Mag;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Recoil;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Accuracy;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float FireRate;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Range;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Damage;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float ReloadSpeed;
	
	float ReloadTime;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float WeaponWeight;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Knockback;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Overheat;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Cooldown;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float DamageFalloff;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float ExplosionRadius;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Stats")
	float Magnification;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Weapon Stats")
    bool bIsProjectile;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Audio")
	USoundCue* GunShotNoise;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Audio")
	USoundCue* ReloadNoise;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon Audio")
	USoundCue* MagEmptyNoise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 1))
	int pellets;

	UPROPERTY()
	UCapsuleComponent* InteractionCapsule;

	UFUNCTION()
	void OnInteractionCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodytypeIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponBody;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponBarrel;

	//These should be static meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponGrip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMagazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponStock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponScope;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WeaponBarrelExtension;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* BarrelSkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* GripSkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* MagazineSkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* StockSkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* ScopeSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BarrelExtensionStaticMesh;

	// Weapon Materials
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterial* WeaponSkin;

	UFUNCTION(BlueprintCallable)
	void UpdateWeaponMesh();

	UFUNCTION(BlueprintCallable)
	virtual FHitResult FireWeapon();

	UFUNCTION(BlueprintCallable)
	virtual void EndFireWeapon();

	UFUNCTION(BlueprintCallable)
	virtual void Reload();

	UFUNCTION()
	int32 CalculateScore(const FHitResult& HitResult);

	UFUNCTION()
	virtual void DealDamage(AZombieBase* Zombie);

	void Reloading();

	UWorld* WorldRef;
	AProjectApocalypseCharacter* PlayerRef;

	FHitResult SingleFire();

	FHitResult BurstFire();

	FHitResult AutoFire();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FiringMode FireMode;

	UPROPERTY(BlueprintReadOnly)
	bool bCanFire;

	UPROPERTY(BlueprintReadWrite)
	bool bIsFiring;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual FHitResult LineTrace();
	FVector LineTrace(FVector startPoint, FVector endPoint);

	FTimerHandle ReloadingTimer;

	FTimerHandle FireRateTimer;

	void FireRateCooldown();

	float FireRatecounter;

	bool IsReloading;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};