// Fill out your copyright notice in the Description page of Project Settings.


#include "Wander.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/DirectionalLight.h"
#include "Kismet/KismetMathLibrary.h"




UWander::UWander()
{
	_wanderRadius = 100.0f;
	_wanderDistance = 100.0f;
	_wanderJitter = 40.0f;

	_wanderTarget = FVector(0);
	_wanderAngle = 0;
}

void UWander::BeginPlay()
{

	_wanderAngle = UKismetMathLibrary::RandomFloatInRange(0.0f, PI * 2);
	_wanderTarget = FVector(cos(_wanderAngle), sin(_wanderAngle), 0) * _wanderRadius;

	FTimerHandle UnusedHandle;
	
	GetOwner()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UWander::UpdateAngle, 0.05, true, 0);

}

FVector UWander::Calculate()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(FMath::RadiansToDegrees(_wanderAngle)));
	_wanderTarget = FVector(cos(_wanderAngle), sin(_wanderAngle), 0) * _wanderRadius;

	FVector targetWorld = GetOwner()->GetActorLocation() + _wanderTarget;

	targetWorld += GetOwner()->GetActorForwardVector() * _wanderDistance;


	
	//DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), targetWorld, FColor::Red, false, 0.1);


	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.1, FColor::Red, targetWorld.ToString());

	return targetWorld - GetOwner()->GetActorLocation();
}

void UWander::UpdateAngle()
{
	_wanderAngle += UKismetMathLibrary::RandomFloatInRange(FMath::DegreesToRadians(-_wanderJitter), FMath::DegreesToRadians(_wanderJitter) );
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.2, FColor::Red, FString::SanitizeFloat(FMath::RadiansToDegrees(_wanderAngle)));

}


