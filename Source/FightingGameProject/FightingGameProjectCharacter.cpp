// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FightingGameProjectGameMode.h"

AFightingGameProjectCharacter::AFightingGameProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	//CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	//SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	hurtbox = nullptr;
	wasFirstAttackUsed = false;
	wasHeavyAttackUsed = false;
	wasMediumAttackUsed = false;
	wasHeavyKickAttackUsed = false;
	playerHealth = 1.00f;
	otherPlayer = nullptr;
	isFlipped = false;
	transform = FTransform();
	scale = FVector(0.0f, 0.0f, 0.0f);
	canAttack = false;
	hasLostRound = false;
	hasWonMatch = false;
	canMove = false;
	maxDistanceApart = 800.0f;
	//directionalInput = EDirectionalInput::VE_Default;

	roundsWon = 0;

    characterClass = ECharacterClass::VE_DEFAULT;
	characterClass = ECharacterClass::VE_XBot;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFightingGameProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (auto gameMode = Cast<AFightingGameProjectGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (gameMode->player1 == this)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 1 has bound their controls."));

			// set up gameplay key bindings
			PlayerInputComponent->BindAction("JumpP1", IE_Pressed, this, &ACharacter::Jump);
			PlayerInputComponent->BindAction("JumpP1", IE_Released, this, &ACharacter::StopJumping);
			PlayerInputComponent->BindAxis("MoveRightP1", this, &AFightingGameProjectCharacter::MoveRight);

			PlayerInputComponent->BindAction("Attack1P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack1);
			PlayerInputComponent->BindAction("Attack2P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack2);
			PlayerInputComponent->BindAction("Attack3P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack3);
			PlayerInputComponent->BindAction("Attack4P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack4);

			PlayerInputComponent->BindTouch(IE_Pressed, this, &AFightingGameProjectCharacter::TouchStarted);
			PlayerInputComponent->BindTouch(IE_Released, this, &AFightingGameProjectCharacter::TouchStopped);

			// set up gameplay key bindings
			PlayerInputComponent->BindAction("JumpP1", IE_Pressed, this, &ACharacter::Jump);
			PlayerInputComponent->BindAction("JumpP1", IE_Released, this, &ACharacter::StopJumping);
			PlayerInputComponent->BindAxis("MoveRightP1", this, &AFightingGameProjectCharacter::MoveRight);

			PlayerInputComponent->BindAction("Attack1P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack1);
			PlayerInputComponent->BindAction("Attack2P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack2);
			PlayerInputComponent->BindAction("Attack3P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack3);
			PlayerInputComponent->BindAction("Attack4P1", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack4);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 2 has bound their controls."));

			//Setup gameplay by key bindings.
			PlayerInputComponent->BindAction("JumpP2", IE_Pressed, this, &ACharacter::Jump);
			PlayerInputComponent->BindAction("JumpP2", IE_Released, this, &ACharacter::StopJumping);
			PlayerInputComponent->BindAxis("MoveRightP2", this, &AFightingGameProjectCharacter::MoveRight);
			PlayerInputComponent->BindAction("Attack1P2", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack1);
			PlayerInputComponent->BindAction("Attack2P2", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack2);
			PlayerInputComponent->BindAction("Attack3P2", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack3);
			PlayerInputComponent->BindAction("Attack4P2", IE_Pressed, this, &AFightingGameProjectCharacter::StartAttack4);
		}
	}
}

void AFightingGameProjectCharacter::MoveRight(float Value)
{
	//if (canMove)
	//{
		//UE_LOG(LogTemp, Warning, TEXT("The directional input is %f"), Value);

		//if (Value < 0.20f)
		//{
			//directionalInput = EDirectionalInput::VE_MovingRight;
		//}
		//else if (Value < -0.20f)
		//{
			//directionalInput = EDirectionalInput::VE_MovingLeft;
		//}
		//else
		//{
			//directionalInput = EDirectionalInput::VE_Default;
		//}

		float currentDistanceApart = abs(otherPlayer->GetActorLocation().Y - GetActorLocation().Y);

		if (currentDistanceApart >= maxDistanceApart)
		{
			if ((currentDistanceApart + Value < currentDistanceApart && !isFlipped) || (currentDistanceApart - Value < currentDistanceApart && isFlipped))
			{
				//Add movement in the direction.
				AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
			}
		}
		else
		{
			//Add movement in the direction.
			AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
		}
	//}
}

void AFightingGameProjectCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AFightingGameProjectCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AFightingGameProjectCharacter::StartAttack1()
{
	if (canAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("We are using our first attack."));
		wasFirstAttackUsed = true;
	}
}

void AFightingGameProjectCharacter::StartAttack2()
{
	if (canAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("We are using our second attack."));
		wasHeavyAttackUsed = true;
	}
}

void AFightingGameProjectCharacter::StartAttack3()
{
	if (canAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("We are using our third attack."));
		wasMediumAttackUsed = true;
	}
}

void AFightingGameProjectCharacter::StartAttack4()
{
	if (canAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("We are using our fourth attack."));
		wasHeavyKickAttackUsed = true;
		TakeDamage(0.05f);
	}
}


void AFightingGameProjectCharacter::P2KeyboardStartAttack1()
{
	StartAttack1();
}

void AFightingGameProjectCharacter::P2KeyboardStartAttack2()
{
	StartAttack2();
}

void AFightingGameProjectCharacter::P2KeyboardStartAttack3()
{
	StartAttack3();
}

void AFightingGameProjectCharacter::P2KeyboardStartAttack4()
{
	StartAttack4();
}

void AFightingGameProjectCharacter::P2KeyboardJump()
{
	Jump();
}

void AFightingGameProjectCharacter::P2KeyboardStopJumping()
{
	StopJumping();
}

void AFightingGameProjectCharacter::P2KeyboardMoveRight(float _value)
{
	MoveRight(_value);
}

void AFightingGameProjectCharacter::TakeDamage(float _damageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("We are taking damage for %f points."), _damageAmount);
	playerHealth -= _damageAmount;

	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}

void AFightingGameProjectCharacter::WinRound()
{
	otherPlayer->hasLostRound = true;
	++roundsWon;
	NotifyRoundEnd();
	UpdateHUDRoundIcons();
}

void AFightingGameProjectCharacter::WinMatch()
{
	canMove = false;
	canAttack = false;
	hasWonMatch = true;
}

//Called every frame.
void AFightingGameProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (otherPlayer)
	{
		if (auto characterMovement = GetCharacterMovement())
		{
			if (auto enemyMovement = otherPlayer->GetCharacterMovement())
			{
				if (enemyMovement->GetActorLocation().Y >= characterMovement->GetActorLocation().Y)
				{
					if (isFlipped)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = -1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}

						isFlipped = false;
					}
				}

				else
				{
					if (!isFlipped)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = -1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}
						isFlipped = true;
					}
				}
			}
		}
	}
}


