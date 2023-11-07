// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectApocalypseGameMode.h"
#include "ProjectApocalypseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectApocalypseGameMode::AProjectApocalypseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
