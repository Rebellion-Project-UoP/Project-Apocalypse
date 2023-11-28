// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycleTest.h"

// Sets default values
ADayNightCycleTest::ADayNightCycleTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADayNightCycleTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADayNightCycleTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (dayLightSource)
	{
		dayLightSource->AddActorLocalRotation(FRotator((DeltaTime * turnRate), 0, 0));
	}

	if (nightLightSource)
	{
		nightLightSource->AddActorLocalRotation(FRotator((DeltaTime * turnRate), 0, 0));
	}

	if (dayLightSource->GetActorRotation().Pitch >= -1)
	{
		dayLightSource->SetActorHiddenInGame(true);
		nightLightSource->SetActorHiddenInGame(false);
		bIsNightTime = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
	}

	if (dayLightSource->GetActorRotation().Pitch <= 1)
	{
		dayLightSource->SetActorHiddenInGame(false);
		nightLightSource->SetActorHiddenInGame(true);
		bIsNightTime = false;
	}

	if (sun)
	{
		FOutputDeviceNull ar;
		sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}
}

