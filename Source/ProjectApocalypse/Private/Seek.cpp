// Fill out your copyright notice in the Description page of Project Settings.


#include "Seek.h"
#include <Kismet/GameplayStatics.h>

USeek::USeek()
{
	seekTargetPos = FVector(0, 0, 0);
}

void USeek::BeginPlay()
{
	

}

FVector USeek::Calculate()
{
	FVector direction = (seekTargetPos - GetOwner()->GetTransform().GetLocation());
	float distance = FVector::Dist(GetOwner()->GetTransform().GetLocation(), seekTargetPos);
	direction.Normalize();
	FVector desiredVelocity = direction * (distance / 50);

	return desiredVelocity;
}
