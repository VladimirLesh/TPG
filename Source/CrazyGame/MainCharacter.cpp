// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"

#include "Item.h"
#include "Weapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f; // The length of the spring arm
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true; // Smoothly move camera to follow the spring arm
	CameraBoom->CameraLagSpeed = 3.f; // Speed of camera movement

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 800.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.5f;

	MaxHealth = 100.f;
	Health = 100.f;
	MaxStamina = 100.f;
	MinStaminaForRunning = 50.f;
	StaminaDrainRate = 25.f;
	Stamina = 100.f;
	Coins = 0.f;

	WalkSpeed = 300.f;
	RunSpeed = 650.f;

	bShiftKeyDown = false;
	bLMBDown = false;
	MovementState = EMovementState::EMS_Walk;
	StaminaState = EStaminaState::ESS_Normal;
	
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float deltaStamina = DeltaTime * StaminaDrainRate;

	switch (StaminaState)
	{
		case EStaminaState::ESS_Normal:{
				if (bShiftKeyDown){
					if (Stamina - deltaStamina <= MinStaminaForRunning){
						SetStaminaState(EStaminaState::ESS_BelowMinimum);
						Stamina -= deltaStamina;
					}
					else{
						Stamina -= deltaStamina;
					}
					
					SetMovementState(EMovementState::EMS_Run);
				}
				else{
					if (Stamina + deltaStamina >= MaxStamina){
						Stamina = MaxStamina;
					}
					else{
						Stamina += deltaStamina;
					}
					SetMovementState(EMovementState::EMS_Walk);
				}
			}
		break;
	case EStaminaState::ESS_BelowMinimum:
			{
				if (bShiftKeyDown)
				{
					if (Stamina - deltaStamina <= 0.f)
					{
						SetStaminaState(EStaminaState::ESS_Exhausted);
						SetMovementState(EMovementState::EMS_Walk);
						Stamina = 0.f;
					}
					else
					{
						SetMovementState(EMovementState::EMS_Run);
						Stamina -= deltaStamina;
					}
				}
				else
				{
					if (Stamina + deltaStamina >= MinStaminaForRunning)
					{
						SetStaminaState(EStaminaState::ESS_Normal);
						Stamina += deltaStamina;
					}
					else
					{
						Stamina += deltaStamina;
					}
					SetMovementState(EMovementState::EMS_Walk);
				}
			}
		break;
	case EStaminaState::ESS_Exhausted :
		{
			if (bShiftKeyDown)
			{
				Stamina = 0.f;
			}
			else{
				SetStaminaState(EStaminaState::ESS_ExhausedRecovering);
				Stamina += deltaStamina;
			}
			SetMovementState(EMovementState::EMS_Walk);
		}
		break;
	case EStaminaState::ESS_ExhausedRecovering :
		{
			if (Stamina + deltaStamina >= MinStaminaForRunning)
			{
				SetStaminaState(EStaminaState::ESS_Normal);
				Stamina += deltaStamina;
			}
			else
			{
				Stamina += deltaStamina;
			}
			SetMovementState(EMovementState::EMS_Walk);
		}
		break;
		
	}

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::ShiftKeyUp);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMainCharacter::LMBUp);
}

void AMainCharacter::MoveForward(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Axis = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Axis, value);
	}
}

void AMainCharacter::MoveRight(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Axis = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Axis, value);
	}
}

void AMainCharacter::TurnAtRate(float value)
{
	AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float value)
{
	AddControllerPitchInput(value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::DecrementHealth(float amount)
{
	if (Health - amount <= 0.f)
	{
		Health -= amount;
		Die();
	}
	else
	{
		Health -= amount;
	}
}

void AMainCharacter::Die()
{
	
}

void AMainCharacter::SetMovementState(EMovementState state)
{
	MovementState = state;

	switch (MovementState)
	{
	case EMovementState::EMS_Walk :
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;
	case EMovementState::EMS_Run :
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		break;
	}
}

void AMainCharacter::IncreaseCoins(int value)
{
	Coins += value;
}

void AMainCharacter::ShiftKeyUp()
{
	bShiftKeyDown = false;
}

void AMainCharacter::ShiftKeyDown()
{
	bShiftKeyDown = true;
}

void AMainCharacter::LMBDown()
{
	if (OverlappedItem)
	{
		AWeapon* weapon = Cast<AWeapon>(OverlappedItem);

		if (weapon)
		{
			weapon->Equip(this);
			SetOverlappedItem(nullptr);
		}
	}
}

void AMainCharacter::LMBUp()
{
	
}

void AMainCharacter::PlayPickupLocations()
{
	for (auto location : PickupLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, location, 25.f, 12, FLinearColor::Green, 5.f);
	}
}


