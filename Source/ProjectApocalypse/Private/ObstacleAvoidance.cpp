// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleAvoidance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ZombieBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"



FVector UObstacleAvoidance::Calculate()
{
	FVector steeringForce = FVector::Zero();


	FVector location = GetOwner()->GetActorLocation();
	FVector fwdVector = GetOwner()->GetActorForwardVector();

	AZombieBase* parent = Cast<AZombieBase>(GetOwner());

	TArray<FHitResult> hits; 
	FVector closestObstacle;
	float forceMulti;



	if (UKismetSystemLibrary::BoxTraceMulti(GetWorld(), location, location + fwdVector * viewDistance, FVector(parent->GetCapsuleComponent()->GetScaledCapsuleRadius()), FRotator::ZeroRotator, ETraceTypeQuery::TraceTypeQuery1,true, TArray<AActor*>(), EDrawDebugTrace::None, hits, true, FLinearColor::Red))
	{
		for (int i = 0; i<  hits.Num(); i++)
		{
			FHitResult hit = hits[i];

			

			if (Cast<ACharacter>(hit.GetActor())) {
				continue;
			}

			

			closestObstacle = UKismetMathLibrary::InverseTransformLocation(parent->GetActorTransform(), hit.Location);

			forceMulti = 1.0f + (viewDistance - closestObstacle.X) / viewDistance;

			steeringForce.Y = (hit.GetActor()->GetComponentsBoundingBox().GetExtent().X - closestObstacle.Y) * forceMulti;

			steeringForce = UKismetMathLibrary::TransformDirection(parent->GetActorTransform(), steeringForce);

			break;
		}
	}

	return steeringForce * 2;

}