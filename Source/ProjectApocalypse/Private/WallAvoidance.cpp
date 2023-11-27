// Fill out your copyright notice in the Description page of Project Settings.


#include "WallAvoidance.h"
#include "Kismet/KismetSystemLibrary.h"


FVector UWallAvoidance::Calculate()
{

	FHitResult hit;

	float penDistance = 0;

	FVector location = GetOwner()->GetActorLocation();
	FVector fwdVector = GetOwner()->GetActorForwardVector();
	
	if (GetWorld()->LineTraceSingleByChannel(hit, location,location + fwdVector * viewDistance, ECollisionChannel::ECC_Visibility)) {
	DrawDebugLine(GetWorld(), location, location + fwdVector * viewDistance, hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 5.0f);



		if (!(hit.GetComponent()->ComponentHasTag("Wall"))) {
			return  FVector::Zero();
		}

		penDistance = FVector::Distance(hit.TraceEnd, hit.TraceEnd - hit.ImpactPoint);

		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Red, FString::SanitizeFloat(penDistance));

		return (hit.Normal * penDistance) * 5;
	}

	

	return FVector::Zero();
}

