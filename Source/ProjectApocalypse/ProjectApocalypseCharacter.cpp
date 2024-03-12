// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectApocalypseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



//////////////////////////////////////////////////////////////////////////
// AProjectApocalypseCharacter


AProjectApocalypseCharacter::AProjectApocalypseCharacter()
{
	CurrentStamina = MaxStamina;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	PlayerScore = 0;

	AmmoCrateReserves = 1;

	HealthPackReserves = 1;

	CurrentItemSelected = 0;

	StaminaRegenDelay = 0.0f;

	IsDead = false;
}

void AProjectApocalypseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	TArray<AActor*> children = TArray<AActor*>();

	GetAllChildActors(children);

	for (auto It = children.CreateConstIterator(); It; ++It)
	{
		ABaseWeapon* weapon = (Cast<ABaseWeapon>(*It));

		if (weapon)
		{
			weaponRef = weapon;
		}
	}

	healthComponent = Cast<UHealthComp>(GetComponentByClass(UHealthComp::StaticClass()));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectApocalypseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectApocalypseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectApocalypseCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started , this, &AProjectApocalypseCharacter::SprintStart);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AProjectApocalypseCharacter::SprintEnd);
	}
}

void AProjectApocalypseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjectApocalypseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectApocalypseCharacter::SprintStart()
{

	GetWorldTimerManager().ClearTimer(StaminaRegenTimerHandle);
	
	if (CurrentStamina > 0 && GetCharacterMovement()->Velocity.Size() > 0)
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Blue, "current drain is ");
		GetWorld()->GetTimerManager().SetTimer(StaminaDrainTimerHandle,this, &AProjectApocalypseCharacter::DrainStamina, 0.1f, true,0.0f);
		IsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		/*GetWorldTimerManager().SetTimer(StaminaDrainTimerHandle, this, &AProjectApocalypseCharacter::DrainStamina, 0.1f, true);*/

	}
}

void AProjectApocalypseCharacter::SprintEnd()
{
	IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetWorldTimerManager().ClearTimer(StaminaDrainTimerHandle);
	
	if (!IsSprinting)
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimerHandle, this, &AProjectApocalypseCharacter::RegenStamina, 0.1f, true, StaminaRegenDelay);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(StaminaRegenTimerHandle);
	}
	
}

void AProjectApocalypseCharacter::DrainStamina()
{
	//CurrentStamina -= 1;
		if (CurrentStamina > 0)
		{
			CurrentStamina -= SprintStaminaDrainRate * 0.1f; // Decrease stamina based on the drain rate and interval
	
	
		}
		if (CurrentStamina <= 0)
		{
			CurrentStamina = 0;
			GetWorldTimerManager().ClearTimer(StaminaDrainTimerHandle);
			SprintEnd(); // Stop sprinting when stamina is depleted
		}
}

void AProjectApocalypseCharacter::RegenStamina()
{
	if (CurrentStamina < MaxStamina)
	{
		CurrentStamina += StaminaRegenRate * 0.1f;
	}

	if (CurrentStamina >= MaxStamina)
	{
		CurrentStamina = MaxStamina;
		GetWorldTimerManager().ClearTimer(StaminaRegenTimerHandle);
		
	}
}
