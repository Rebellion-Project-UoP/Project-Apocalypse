// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "AssaultRifle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAPOCALYPSE_API AAssaultRifle : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual FHitResult FireWeapon() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
