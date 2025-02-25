// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ColliderPawn.generated.h"

UCLASS()
class CRAZYGAME_API AColliderPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AColliderPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "MeshComponent")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "MeshComponent")
	class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, Category = "CameraComponent")
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = "CameraComponent")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "ColliderMovementC")
	class UColliderMovementC* ColliderMovementC;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* NewMeshComponent) { MeshComponent = NewMeshComponent; }
	FORCEINLINE USphereComponent* GetSphereComponent() const { return SphereComponent; }
	FORCEINLINE void SetMeshComponent(USphereComponent* NewSphereComponent) { SphereComponent = NewSphereComponent; }
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return Camera; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* NewCameraComponent) { Camera = NewCameraComponent; }
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const { return SpringArm; }
	FORCEINLINE void SetSprngArmComponent(USpringArmComponent* NewSpringArmComponent) { SpringArm = NewSpringArmComponent; } 

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
};


