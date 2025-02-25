 // Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"

#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"

 // Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxCollider->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapBegin);
 	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapEnd);

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	SwitchTime = 2.f;
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();

	InitialDoorLocation = Door->GetComponentLocation();
	InitialSwitchLocation = FloorSwitch->GetComponentLocation();
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 void AFloorSwitch::UpdateDoorLocaiton(float Z)
 {
	FVector NewLocation = InitialDoorLocation;
	NewLocation.Z += Z;
	Door->SetWorldLocation(NewLocation);
 }

void AFloorSwitch::UpdateSwitchLocaiton(float Z)
{
	FVector NewLocation = InitialSwitchLocation;
	NewLocation.Z += Z;
	FloorSwitch->SetWorldLocation(NewLocation);
}

 void AFloorSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
 	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));

	if (!bIsCharacterOnFloor)
		bIsCharacterOnFloor = true;
	
	RaiseDoor();
	RaiseSwitch();
}

void AFloorSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
 	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));

    if (bIsCharacterOnFloor)
    	bIsCharacterOnFloor = false;
	
	GetWorldTimerManager().SetTimer(SwitchHandle, this, &AFloorSwitch::CloseDoor, SwitchTime, false);
}

void AFloorSwitch::CloseDoor()
{
	if (!bIsCharacterOnFloor)
	{
		LowerDoor();
		LowerSwitch();
	}
}

