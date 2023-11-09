// Fill out your copyright notice in the Description page of Project Settings.


#include "Wander.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/DirectionalLight.h"


void UWander::BeginPlay()
{
	//navMesh = Cast<ANavMeshBoundsVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), ANavMeshBoundsVolume::StaticClass()));
}

FVector UWander::Calculate()
{

	return FVector();
}
