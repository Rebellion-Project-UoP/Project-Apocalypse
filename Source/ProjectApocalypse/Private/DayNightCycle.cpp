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

	if (lightSource)
	{
		lightSource->AddActorLocalRotation(FRotator(0, (DeltaTime * turnRate), 0));

		if (lightSource->GetActorRotation() == FRotator(0, 180, 0))
		{
			if (sun)
			{
				//Night->SetMaterial()
			}
		}
	}

	//if (sun)
	//{
	//	FOutputDeviceNull ar;
	//	sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);

	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("True"));
	//}
}

