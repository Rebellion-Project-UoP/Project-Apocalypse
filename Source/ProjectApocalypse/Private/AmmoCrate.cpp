// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCrate.h"


void AAmmoCrate::PickUpAction(AProjectApocalypseCharacter* player)
{
	player->AmmoCrateReserves++;
}

void AAmmoCrate::UseAction(AProjectApocalypseCharacter* player)
{	
	if (player->AmmoCrateReserves > 0)
	{
		if (player->weaponRef->Ammunition < player->weaponRef->MaxAmmunition)
		{
			//player->weaponRef->Ammunition += 30;
			player->weaponRef->Ammunition = player->weaponRef->MaxAmmunition;

			if (player->weaponRef->Ammunition > player->weaponRef->MaxAmmunition)
			{
				player->weaponRef->Ammunition = player->weaponRef->MaxAmmunition;
			}

			player->AmmoCrateReserves--;
		}
	}
}
