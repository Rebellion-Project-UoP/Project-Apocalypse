// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCrate.h"


void AAmmoCrate::PickUpAction(AProjectApocalypseCharacter* player)
{
	Super::PickUpAction(player);
	player->AmmoCrateReserves++;
}

void AAmmoCrate::UseAction(AProjectApocalypseCharacter* player, bool& outActionUsed)
{	
	outActionUsed = false;

	if (player->AmmoCrateReserves > 0)
	{
		if (player->weaponRef->Ammunition < player->weaponRef->MaxAmmunition)
		{
			player->weaponRef->Ammunition = player->weaponRef->MaxAmmunition+player->weaponRef->MagSize-player->weaponRef->Mag;

			player->AmmoCrateReserves--;

			outActionUsed = true;
		}
	}
}
