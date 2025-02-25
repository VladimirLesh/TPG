// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UserWidgetAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, UserWidgetAsset);
		if (HUDOverlay)
		{
			UE_LOG(LogTemp, Warning, TEXT("HUD Widget created successfully!"));
			HUDOverlay->AddToViewport(0);  // Указываем ZOrder
			HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create HUD Widget!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UserWidgetAsset is not set!"));
	}
}
