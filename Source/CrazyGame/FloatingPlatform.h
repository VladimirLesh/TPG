// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class CRAZYGAME_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingPlatform")
	FVector StartPoint;

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget))
	FVector EndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingPlatform")
	float InterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingPlatform")
	float InterpTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingPlatform")
	bool bInterping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingPlatform")
	float FloatingDistance;

	FTimerHandle InterpTimer;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void toggleInterping();
	void swapVectors(FVector& start, FVector& end);

};

