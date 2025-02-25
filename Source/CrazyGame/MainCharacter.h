// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	EMS_Walk UMETA(DisplayName = "Walk"),
	EMS_Run UMETA(DisplayName = "Run"),
	EMS_Jump UMETA(DisplayName = "Jump"),
	EMS_Fall UMETA(DisplayName = "Fall"),
	EMS_MAX UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EStaminaState : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhausedRecovering UMETA(DisplayName = "ExhausedRecovering"),
	ESS_MAX UMETA(DisplayName = "Max")
}; 

UCLASS()
class CRAZYGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	AMainCharacter();

	TArray<FVector> PickupLocations;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AItem* OverlappedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ENUM")
	EMovementState MovementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ENUM")
	EStaminaState StaminaState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Camera);
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Camera);
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats");
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats");
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float StaminaDrainRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float MinStaminaForRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float Coins;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementState");
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementState");
	float RunSpeed;

	bool bShiftKeyDown;
	bool bLMBDown;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void TurnAtRate(float value);
	void LookUpAtRate(float value);

	void DecrementHealth(float amount);
	void Die();
	void SetMovementState(EMovementState state);
	void IncreaseCoins(int value);

	void ShiftKeyDown();
	void ShiftKeyUp();
	void LMBDown();
	void LMBUp();

	UFUNCTION(BlueprintCallable)
	void PlayPickupLocations();

	FORCEINLINE class USpringArmComponent* GetSpringComponent() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return Camera; }
	FORCEINLINE void SetStaminaState(EStaminaState state) { StaminaState = state; }
	FORCEINLINE void SetEquippedWeapon(AWeapon* weapon) { EquippedWeapon = weapon; }
	FORCEINLINE void SetOverlappedItem(AItem* item) { OverlappedItem = item; }
};
