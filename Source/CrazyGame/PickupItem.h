// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYGAME_API APickupItem : public AItem
{
	GENERATED_BODY()

	public:
	APickupItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupItem")
	int CoinCount;

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
