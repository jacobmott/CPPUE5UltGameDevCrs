// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPUE5UltGameDevCrsGameMode.h"
#include "CPPUE5UltGameDevCrsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPPUE5UltGameDevCrsGameMode::ACPPUE5UltGameDevCrsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
