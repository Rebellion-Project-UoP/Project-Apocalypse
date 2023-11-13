// Fill out your copyright notice in the Description page of Project Settings.


#include "Wander.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/DirectionalLight.h"



UWander::UWander()
{
	_wanderRadius = 0.0f;
	_wanderDistance = 0.0f;
	_wanderJitter = 0.0f;

	_wanderTarget = FVector(0);
	_wanderAngle = 0;
}

void UWander::BeginPlay()
{
	_wanderAngle = FMath::RandRange(0.0f, PI * 2);
	_wanderTarget = FVector(cos(_wanderAngle), sin(_wanderAngle), 0);

	FTimerHandle UnusedHandle;
	
	GetOwner()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UWander::UpdateAngle, 0.1, true, 0);

}

FVector UWander::Calculate()
{


	_wanderTarget = FVector(cos(_wanderAngle), sin(_wanderAngle), 0);

	FVector targetWorld = GetOwner()->GetActorLocation() + _wanderTarget;

	targetWorld += GetOwner()->GetActorLocation().ForwardVector * _wanderDistance;
	
	return targetWorld - GetOwner()->GetActorLocation();
}

void UWander::UpdateAngle()
{
	_wanderAngle += FMath::RandRange(-_wanderJitter, _wanderJitter);

}


