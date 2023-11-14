// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"

void AAssaultRifle::FireWeapon()
{
	Super::FireWeapon();

	UE_LOG(LogTemp, Warning , TEXT("bang"));
}

void AAssaultRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
