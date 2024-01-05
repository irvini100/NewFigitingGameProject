// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightingGameProjectCharacter.h"
#include "FightingGameProjectGameMode.generated.h"

UCLASS(minimalapi)
class AFightingGameProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFightingGameProjectGameMode();

	//Reference player 1 and 2 spawn points.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFightingGameProjectCharacter* player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFightingGameProjectCharacter* player2;

	//The time for each round (this can be overwritten by the value in MyGameInstance.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	float roundTime;

	//The number of rounds each fight lasts (this can be best of # or must win # and can be overwritten by the value of MyGameInstance).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	int numRounds;

	//Should the round timer continously go down at the current time?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Settings")
	bool isTimerActive;
};





