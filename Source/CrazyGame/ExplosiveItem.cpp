// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveItem.h"
#include "MainCharacter.h"

AExplosiveItem::AExplosiveItem()
{
	Damage = 10.f;
}

void AExplosiveItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		AMainCharacter* MyCharacter = Cast<AMainCharacter>(OtherActor);

		if (MyCharacter)
		{
			MyCharacter->DecrementHealth(Damage);
			Destroy();
		}
	}
}

void AExplosiveItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
