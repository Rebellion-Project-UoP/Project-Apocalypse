// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ProjectApocalypseCharacter.generated.h"


UCLASS(config = Game)
class AProjectApocalypseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;



public:
	AProjectApocalypseCharacter();


protected:
	/** Called for Sprint input */
	void SprintStart();
	void SprintEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 900.f;


	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool IsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float SprintStaminaDrainRate = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaRegenRate = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	// Maximum health the player can have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;

	// Player's current hunger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hunger")
	float Hunger;

	// Maximum hunger the player can have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hunger")
	float MaxHunger = 100.f;

	// Rate at which hunger affects health (modify as needed)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hunger")
	float HungerHealthRate = 1.0f;

	// Time interval for hunger increase (modify as needed)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hunger")
	float HungerIncreaseInterval = 5.0f;


	//UFUNCTION(BlueprintCallable, Category = "Player")
	//void TakeDamage(float DamageAmount);

	//// Function to check if the player is alive
	//UFUNCTION(BlueprintPure, Category = "Player")
	//bool IsAlive() const;

	//// Function to handle hunger
	//UFUNCTION(BlueprintCallable, Category = "Player")
	//void IncreaseHunger(float HungerIncrease);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void IncreaseHungerOverTime();

	// Function to deplete health based on hunger
	UFUNCTION(BlueprintCallable, Category = "Player")
	void DepleteHealth();


	UFUNCTION()
	void RegenStamina();

	UFUNCTION()
	void DrainStamina();

	UFUNCTION()
	void PrintCurrentStats();

	void Tick(float DeltaTime);

	FTimerHandle StaminaDrainTimerHandle;
	FTimerHandle StaminaRegenTimerHandle;

	bool bShouldDepleteHealth;

	//float StaminaUsageRate;
	//float StaminaRegenRate;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

