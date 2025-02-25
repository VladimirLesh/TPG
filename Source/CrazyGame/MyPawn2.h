// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn2.generated.h"

UCLASS()
class CRAZYGAME_API AMyPawn2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "MeshComponent")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "XXX")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "XXX")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "XXX")
	class UMyPawn2MovementComponent* MovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void PitchCamera(float value);
	void YawCamera(float value);

	FVector2d CameraInput;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* NewMeshComponent) { MeshComponent = NewMeshComponent; }

};
