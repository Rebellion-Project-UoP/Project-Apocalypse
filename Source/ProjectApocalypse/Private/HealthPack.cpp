// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"

void AHealthPack::PickUpAction(AProjectApocalypseCharacter* player)
{
	player->HealthPackReserves++;
}

void AHealthPack::UseAction(AProjectApocalypseCharacter* player)
{
	if (player->HealthPackReserves > 0)
	{
		player->healthComponent->currHealth = 100;

		player->HealthPackReserves--;
	}
}
