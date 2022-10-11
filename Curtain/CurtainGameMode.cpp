// Copyright Epic Games, Inc. All Rights Reserved.

#include "CurtainGameMode.h"
#include "CurtainCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACurtainGameMode::ACurtainGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
