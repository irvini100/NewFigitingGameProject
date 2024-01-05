// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameProjectGameMode.h"
#include "FightingGameProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFightingGameProjectGameMode::AFightingGameProjectGameMode()
{
	//set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//Set the default values for variables.
	numRounds = 2;
	roundTime = 99;
	isTimerActive = false;
}
