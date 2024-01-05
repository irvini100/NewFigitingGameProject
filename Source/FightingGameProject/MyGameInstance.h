// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	VE_DEFAULT UMETA(DisplayName = "Mannequin"),
	VE_XBot UMETA(DisplayName = "Bob")
	//VE_NINJA UMETA(DisplayName = "Ninja")
};

UCLASS()
class FIGHTINGGAMEPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	ECharacterClass P1characterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	ECharacterClass P2characterClass;

	//Is the device intended to be used for multiple players (keyboard mode)?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	bool isDeviceForMultipleplayers;

	//The time for each round (this can be a default/forced value or changed in the options menu.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance Settings")
	float roundTime;

	//The number of rounds each fight lasts (this can be best of # or must win #, and can be a defaoult/forced value or changed in the options menu.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance Settings")
	int numRounds;
};
