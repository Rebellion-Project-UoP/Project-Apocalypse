// Fill out your copyright notice in the Description page of Project Settings.


#include "Separation.h"

void USeparation::BeginPlay() 
{
	parent = Cast<AZombieBase>(GetOwner());
}


FVector USeparation::Calculate()
{

	FVector steeringForce = FVector::Zero();

	TArray<AActor*> neighbours = parent->neighbourhood->neighbours;

	for (int i = 0; i < neighbours.Num(); i++)
	{
		AActor* n = neighbours[i];

		FVector toParent = parent->GetActorLocation() - n->GetActorLocation();

		float distance = toParent.Length();

		toParent.Normalize();
		
		distance -= parent->GetCapsuleComponent()->GetScaledCapsuleRadius();
		toParent /= distance;

		steeringForce += toParent;
	}

	steeringForce *= 5;

	return steeringForce;
}
