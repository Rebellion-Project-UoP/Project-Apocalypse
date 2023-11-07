// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"
#include "Engine/DirectionalLight.h"
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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	AActor* SunLight;

	TArray<AActor*> SunLight;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), SunLight)
	
	
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

