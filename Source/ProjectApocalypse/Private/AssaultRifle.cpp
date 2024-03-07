// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"

FHitResult AAssaultRifle::FireWeapon()
{
	UE_LOG(LogTemp, Warning , TEXT("bang"));

	return Super::FireWeapon();
}

void AAssaultRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
