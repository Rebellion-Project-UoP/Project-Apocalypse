#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

UCLASS()
class PROJECTAPOCALYPSE_API ADayNightCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightCycle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Sky")
	AActor* sun;

	UPROPERTY(EditAnywhere, Category = "Sky")
	ADirectionalLight* dayLightSource;

	UPROPERTY(EditAnywhere, Category = "Sky")
	ADirectionalLight* nightLightSource;

	UPROPERTY(EditAnywhere, Category = "Sky")
	float turnRate;

	UPROPERTY(BlueprintReadOnly, Category = "Environment")
	bool bIsNightTime = false;
};
