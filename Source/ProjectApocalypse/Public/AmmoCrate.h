// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ProjectApocalypse/ProjectApocalypseCharacter.h>
#include "ItemBaseClass.h"
#include "AmmoCrate.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAPOCALYPSE_API AAmmoCrate : public AItemBaseClass
{
	GENERATED_BODY()

public:
	virtual void PickUpAction(AProjectApocalypseCharacter* player) override;

	virtual void UseAction(AProjectApocalypseCharacter* player, bool& outActionUsed) override;
};
