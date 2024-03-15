#pragma once
#include "CoreMinimal.h"
#include "SteeringBehaviour.h"
#include "ZombieController.h"
#include "NeighbourhoodRadius.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "HealthComp.h"
#include "ZombieBase.generated.h"
UCLASS()
class PROJECTAPOCALYPSE_API AZombieBase : public ACharacter
{
	GENERATED_BODY()

public:
	//stores the zombies aggro range
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float aggroRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool playerDetected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDead;

	UFUNCTION(BlueprintCallable)
		FVector getSteeringVelocity();

		UNeighbourhoodRadius* neighbourhood;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float maxWalkSpeed;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float maxRunSpeed;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float damage;

	UHealthComp* healthComponent;

	bool hasPointsBeenReceived;


		
private:
	FVector _velocity;

	UBoxComponent* swipeHitBox;

	//stores all steering behaviours for the zombie
	TArray<USteeringBehaviour*> _behaviours;

	//USkeletalMeshComponent* _skeletalMesh;

public:
	// Sets default values for this character's properties
	AZombieBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
		void Flinch();

	UFUNCTION(BlueprintImplementableEvent)
		void Death();

	void Move();
	
};
