// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"

void AHealthPack::PickUpAction(AProjectApocalypseCharacter* player)
{
	player->HealthPackReserves++;
}

void AHealthPack::UseAction(AProjectApocalypseCharacter* player, bool& outActionUsed)
{
	outActionUsed = false;

	if (player->HealthPackReserves > 0)
	{
		if (player->healthComponent->currHealth < player->healthComponent->maxHealth && player->healthComponent->currHealth > 0)
		{
			player->healthComponent->currHealth = player->healthComponent->maxHealth;

			player->HealthPackReserves--;

			outActionUsed = true;
		}
	}
}
