// Fill out your copyright notice in the Description page of Project Settings.


#include "Seek.h"
#include <Kismet/GameplayStatics.h>

USeek::USeek()
{
	_seekTargetPos = FVector(0, 0, 0);
}

void USeek::BeginPlay()
{
	_playerRef = Cast<AProjectApocalypseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	

}

FVector USeek::Calculate()
{
	_seekTargetPos = _playerRef->GetActorTransform().GetLocation();

	FVector desiredVelocity = (_seekTargetPos - GetOwner()->GetTransform().GetLocation()).Normalize() * FVector(10);

	return FVector();
}
