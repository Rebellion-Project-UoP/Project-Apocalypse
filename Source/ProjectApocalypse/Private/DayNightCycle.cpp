// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADayNightCycle::ADayNightCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADayNightCycle::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (dayLightSource)
	{
		dayLightSource->AddActorLocalRotation(FRotator((DeltaTime * turnRate), 0, 0));
		nightLightSource->AddActorLocalRotation(FRotator((DeltaTime * turnRate), 0, 0));

		if (dayLightSource->GetActorRotation().Pitch >= -1)
		{
			dayLightSource->SetActorHiddenInGame(true);
			nightLightSource->SetActorHiddenInGame(false);
		}

		if (dayLightSource->GetActorRotation().Pitch <= 1)
		{
			dayLightSource->SetActorHiddenInGame(false);
			nightLightSource->SetActorHiddenInGame(true);
		}
	}
}

