// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"

#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPoint()
{
	FVector extent = BoxComponent->GetScaledBoxExtent();
	FVector Origin = BoxComponent->GetComponentLocation();
	FVector point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, extent);
	return point;
}

void ASpawnVolume::SpawnPawn_Implementation(UClass* ToSpawn, const FVector& Location)
{
	UWorld* world = GetWorld();
	FActorSpawnParameters spawnParams;

	if (world)
	{
		AMyPawn* newPawn = world->SpawnActor<AMyPawn>(ToSpawn, Location, FRotator::ZeroRotator, spawnParams);
	}
}


