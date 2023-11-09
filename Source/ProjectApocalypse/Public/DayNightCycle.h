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
	ADirectionalLight* lightSource;

	UPROPERTY(EditAnywhere, Category = "Sky")
	float turnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	UStaticMesh* Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	UStaticMesh* Night;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset


	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Script/Engine.MaterialInstanceConstant'/Engine/MapTemplates/Sky/M_Procedural_Sky_Night.M_Procedural_Sky_Night'"));
	//UStaticMesh* Asset = MeshAsset;

	float toleranceLevels = 1;

};
