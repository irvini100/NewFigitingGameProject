// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FightingGameProjectCharacter.h"
#include "XBot.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGGAMEPROJECT_API AXBot : public AFightingGameProjectCharacter
{
	GENERATED_BODY()

public:
	//Set default values for this character's properties.
	AXBot();

protected:
	//Called when the game starts or when spaned.
	virtual void BeginPlay() override;

public:
	//Called every frame.
	virtual void Tick(float DeltaTime) override;

	//Called to bind functionality to input.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
