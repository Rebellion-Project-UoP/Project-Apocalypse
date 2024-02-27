// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"

void AHealthPack::PickUpAction(AProjectApocalypseCharacter* player)
{

	player->HealthPackReserves++;
}
