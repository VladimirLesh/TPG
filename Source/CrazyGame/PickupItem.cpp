// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupItem.h"
#include "MainCharacter.h"

APickupItem::APickupItem()
{
	CoinCount = 1;
}

void APickupItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		AMainCharacter* MyCharacter = Cast<AMainCharacter>(OtherActor);

		if (MyCharacter){
			MyCharacter->IncreaseCoins(CoinCount);
			MyCharacter->PickupLocations.Add(GetActorLocation());
			Destroy();
		}
	}
}

void APickupItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	
}
