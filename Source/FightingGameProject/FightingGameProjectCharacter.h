// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyGameInstance.h"
#include "FightingGameProjectCharacter.generated.h"

UCLASS(config=Game)
class AFightingGameProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	void StartAttack1();
	void StartAttack2();
	void StartAttack3();
	void StartAttack4();

	//When in keyboard only mode, use these functions to perform actions with player 2.
	UFUNCTION(BlueprintCallable)
	void P2KeyboardStartAttack1();

	UFUNCTION(BlueprintCallable)
	void P2KeyboardStartAttack2();


	UFUNCTION(BlueprintCallable)
	void P2KeyboardStartAttack3();

	UFUNCTION(BlueprintCallable)
	void P2KeyboardStartAttack4();

	UFUNCTION(BlueprintCallable)
	void P2KeyboardJump();

	UFUNCTION(BlueprintCallable)
	void P2KeyboardStopJumping();

	UFUNCTION(BlueprintCallable)
	void P2KeyboardMoveRight(float _value);


protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	AActor* hurtbox;
	//This allows you to transfer between a widget to in game.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	//ECharacterClass CharacterClass;

	//Damage the player
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _damageAmount);

	void Tick(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFightingGameProjectCharacter* otherPlayer;

	//Has the player used the basic attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasFirstAttackUsed;

	//Has the player used the high punch attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasHeavyAttackUsed;

	//Has the player used the low kick.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasMediumAttackUsed;

	//Has the player used the high kick.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasHeavyKickAttackUsed;

	//Is the the character currently able to attack?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool canAttack;

	//The amount of health the character currently has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float playerHealth;
	// End of APawn interface

	//Is the character's model flipped.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	bool isFlipped;

	//The character's transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FTransform transform;

	//The character's scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FVector scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	bool isDeviceForMultiplePlayers;

	//The current class of the character (mannequin, xbot, etc).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Details")
	ECharacterClass characterClass;

	UFUNCTION(BlueprintCallable)
	void WinRound();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void NotifyRoundStart();

	UFUNCTION(BlueprintImplementableEvent)
	void NotifyRoundEnd();

	UFUNCTION(BlueprintCallable)
	void WinMatch();

	//Is this player knocked down due to round loss?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool hasLostRound;

	//The amount of rounds won by character.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logic")
	int roundsWon;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHUDRoundIcons();

	//Has this character won the match?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool hasWonMatch;

	//Is the character currently able to move?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool canMove;

	//The maximum amount of distance that the players can be apart.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float maxDistanceApart;

	//The direction the character is moving or the direction the player is holding down (could be stationary due to blocking or other reasons.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	//EDirectionalInput directionalInput;


public:
	AFightingGameProjectCharacter();

	/** Returns SideViewCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
