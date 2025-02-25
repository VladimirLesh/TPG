// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn2.h"

#include "MyPawn2MovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPawn2::AMyPawn2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f; // The length of the spring arm
	SpringArm->bEnableCameraLag = true; // Smoothly move camera to follow the spring arm
	SpringArm->CameraLagSpeed = 3.f; // Speed of camera movement

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MovementComponent = CreateDefaultSubobject<UMyPawn2MovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	CameraInput = FVector2d(0.0f, 0.0f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyPawn2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();

	CurrentRotation.Yaw += CameraInput.X;
	SetActorRotation(CurrentRotation);

	FRotator CameraRotation = SpringArm->GetComponentRotation();
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch += CameraInput.Y, -80.0f, -15.0f);
	SpringArm->SetWorldRotation(CameraRotation);

}

UPawnMovementComponent* AMyPawn2::GetMovementComponent() const
{
	return MovementComponent;
}

void AMyPawn2::MoveForward(float value)
{
	FVector ForwardVector = GetActorForwardVector();
	MovementComponent->AddInputVector(ForwardVector * value, true);
}

void AMyPawn2::MoveRight(float value)
{
	FVector RightVector = GetActorRightVector();
	MovementComponent->AddInputVector(RightVector * value, true);
}

void AMyPawn2::PitchCamera(float value)
{
	CameraInput.Y = value;
}

void AMyPawn2::YawCamera(float value)
{
	CameraInput.X = value;
}

// Called to bind functionality to input
void AMyPawn2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForvard", this, &AMyPawn2::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawn2::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AMyPawn2::PitchCamera);
	PlayerInputComponent->BindAxis("CameraYaw", this, &AMyPawn2::YawCamera);

}

