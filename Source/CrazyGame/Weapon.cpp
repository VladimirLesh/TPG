// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "MainCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AWeapon::AWeapon()
{
	Mesh->SetCollisionResponseToChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	bWeaponParticles = false;
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		AMainCharacter* MyCharacter = Cast<AMainCharacter>(OtherActor);

		if (MyCharacter)
		{
			MyCharacter->SetOverlappedItem(this);
		}
	}
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{
		AMainCharacter* MyCharacter = Cast<AMainCharacter>(OtherActor);

		if (MyCharacter)
		{
			MyCharacter->SetOverlappedItem(nullptr);
		}
	}
}

void AWeapon::Equip(AMainCharacter* character)
{
	if (character){
		Mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		Mesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* socket = character->GetMesh()->GetSocketByName("hand_rSocket");
		if (socket)
		{
			socket->AttachActor(this, character->GetMesh());
			bRotate = false;
			character->SetEquippedWeapon(this);
			character->SetOverlappedItem(nullptr);
		}

		if (EquippedSound) UGameplayStatics::PlaySound2D(this, EquippedSound);

		if (bWeaponParticles)
		{
			IdleParticleComponent->Deactivate();
		}
	}
}
