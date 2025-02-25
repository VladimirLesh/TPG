// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderPawn.h"

#include "ColliderMovementC.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AColliderPawn::AColliderPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName("Pawn");

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

	ColliderMovementC = CreateDefaultSubobject<UColliderMovementC>(TEXT("ColliderMovementC"));
	ColliderMovementC->UpdatedComponent = RootComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0; 
}

// Called when the game starts or when spawned
void AColliderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColliderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AColliderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForvard", this, &AColliderPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AColliderPawn::MoveRight);

}

void AColliderPawn::MoveRight(float Value)
{
	FVector RIghtVector = GetActorRightVector();
	
	if (ColliderMovementC)
		ColliderMovementC->AddInputVector(RIghtVector * Value);
}

void AColliderPawn::MoveForward(float Value)
{
	FVector ForwardVector = GetActorForwardVector();
	
	if (ColliderMovementC)
		ColliderMovementC->AddInputVector(ForwardVector * Value);
}

UPawnMovementComponent* AColliderPawn::GetMovementComponent() const
{
	return ColliderMovementC;
}

