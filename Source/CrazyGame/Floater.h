// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class CRAZYGAME_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Floater Vector")
	FVector InitialLocation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, category = "Floater Vector")
	FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Floater Vector")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Vector")
	FVector InitialDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Vector")
	bool bIsShouldFloat;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Floater Vector")
	bool bInitializedFloaterLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Floater Vector | Wave parameters")
	float Amplitude = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Floater Vector | Wave parameters")
	float TimeStretch = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Floater Vector | Wave parameters")
	float C = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Floater Vector | Wave parameters")
	float time = 0.0f;

};
