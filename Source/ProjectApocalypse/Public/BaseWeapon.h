// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

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

	
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponBody;
	UPROPERTY()
	USkeletalMeshComponent* WeaponBarrel;

	//These should be static meshes
	UPROPERTY()
	USkeletalMeshComponent* WeaponGrip;
	UPROPERTY()
	USkeletalMeshComponent* WeaponMagazine;
	UPROPERTY()
	USkeletalMeshComponent* WeaponStock;
	UPROPERTY()
	USkeletalMeshComponent* WeaponScope;

	UPROPERTY()
	UStaticMeshComponent* WeaponBarrelExtension;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* BarrelSkeletalMesh = NewObject<USkeletalMesh>();

	//These should be static meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* GripSkeletalMesh = NewObject<USkeletalMesh>();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* MagazineSkeletalMesh = NewObject<USkeletalMesh>();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* StockSkeletalMesh = NewObject<USkeletalMesh>();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* ScopeSkeletalMesh = NewObject<USkeletalMesh>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BarrelExtensionStaticMesh = NewObject<UStaticMesh>();

	// Weapon Materials
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterial* WeaponSkin;

	UFUNCTION(BlueprintCallable)
	void UpdateWeaponMesh();

	UFUNCTION(BlueprintCallable)
	virtual void FireWeapon();
	
	// UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Weapon Stats")
	// ENUM FiringMode;
	// Single fire
	// Burst-fire
	// Auto-fire
	// Toggleable
	// Binary trigger

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};