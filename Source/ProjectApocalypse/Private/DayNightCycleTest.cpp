// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycleTest.h"

// Sets default values
ADayNightCycleTest::ADayNightCycleTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rotationTimeInSeconds = 180.0f;
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

	float RotationAngle = 360.0f * (DeltaTime / rotationTimeInSeconds);

	if (dayLightSource)
	{
		dayLightSource->AddActorLocalRotation(FRotator((RotationAngle), 0, 0));
	}

	if (nightLightSource)
	{
		nightLightSource->AddActorLocalRotation(FRotator((RotationAngle), 0, 0));
	}

	if (sun)
	{
		FOutputDeviceNull ar;
		sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}
}

