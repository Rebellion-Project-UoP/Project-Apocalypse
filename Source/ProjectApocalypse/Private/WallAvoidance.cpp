// Fill out your copyright notice in the Description page of Project Settings.


#include "WallAvoidance.h"
#include "Kismet/KismetSystemLibrary.h"


FVector UWallAvoidance::Calculate()
{

	FVector steeringForce = FVector::Zero();

	FHitResult hit;

	float penDistance = 0;

	FVector location = GetOwner()->GetActorLocation();
	FVector fwdVector = GetOwner()->GetActorForwardVector();

	FCollisionQueryParams CollisionParameters;

	CollisionParameters.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(hit, location, location + fwdVector * viewDistance, ECollisionChannel::ECC_Visibility, CollisionParameters)) {


		if (hit.GetComponent()->ComponentHasTag("Wall")) {

			penDistance = FVector::Distance(hit.TraceEnd, hit.TraceEnd - hit.ImpactPoint);

			steeringForce += (hit.Normal * penDistance);
		}
	}

	FHitResult hitRight;

	if (GetWorld()->LineTraceSingleByChannel(hitRight, location, location + (fwdVector + GetOwner()->GetActorRightVector()) * (viewDistance / 3), ECollisionChannel::ECC_Visibility, CollisionParameters)) {
		if (hitRight.GetComponent()->ComponentHasTag("Wall")) {
			penDistance = FVector::Distance(hitRight.TraceEnd, hitRight.TraceEnd - hitRight.ImpactPoint);

			steeringForce += (hitRight.Normal * penDistance);
		}
	}

	FHitResult hitLeft;

	if (GetWorld()->LineTraceSingleByChannel(hitLeft, location, location + (fwdVector - GetOwner()->GetActorRightVector()) * (viewDistance / 3), ECollisionChannel::ECC_Visibility, CollisionParameters)) {
		if (hitLeft.GetComponent()->ComponentHasTag("Wall")) {
			penDistance = FVector::Distance(hitLeft.TraceEnd, hitLeft.TraceEnd - hitLeft.ImpactPoint);

			steeringForce += (hitLeft.Normal * penDistance);

		}
	}

	return steeringForce * 6;
}

