// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	InitialLocation = FVector(0, 0, 0);
	PlacedLocation = FVector(0, 0, 0);
	WorldOrigin = FVector(0, 0, 0);
	InitialDirection = FVector(0, 0, 0);
	
	bInitializedFloaterLocation = true;
	bIsShouldFloat = false;
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();
	float x = FMath::RandRange(-100, 100);
	float y = FMath::RandRange(-100, 100);
	float z = FMath::RandRange(-100, 100);
	InitialLocation = FVector(x, y, z);

	PlacedLocation = GetActorLocation();
	
	if (bInitializedFloaterLocation)
	{
		SetActorLocation(InitialLocation);
	}
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShouldFloat)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = NewLocation.Z + Amplitude * FMath::Sin(TimeStretch * time) + C;

		SetActorLocation(NewLocation);
		time += DeltaTime;
	}

}

