// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingPlatform.h"
#include "TimerManager.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	StartPoint = FVector(0.0f);
	EndPoint = FVector(0.0f);
	bInterping = false;
	FloatingDistance = 0.0f;
	InterpSpeed = 1.0f;
	InterpTime = 1.0f;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint += StartPoint;
	FloatingDistance = (EndPoint - StartPoint).Size();
	
	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::toggleInterping, InterpTime);
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterping)
	{
		FVector currentLocation = GetActorLocation();
		FVector interp = FMath::VInterpTo(currentLocation, EndPoint, DeltaTime, InterpSpeed);
	
		SetActorLocation(interp);

		float distanceTraveled = (GetActorLocation() - StartPoint).Size();

		if (FloatingDistance - distanceTraveled <= 1.0f)
		{
			toggleInterping();
			GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::toggleInterping, InterpTime);
			swapVectors(StartPoint, EndPoint);
		}
	}
}

void AFloatingPlatform::toggleInterping()
{
	bInterping = !bInterping;
}

void AFloatingPlatform::swapVectors(FVector& start, FVector& end)
{
	FVector temp = start;
	start = end;
	end = temp;
}

