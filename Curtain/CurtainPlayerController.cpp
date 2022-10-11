// Fill out your copyright notice in the Description page of Project Settings.


#include "CurtainPlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"

void ACurtainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (BP_HUDWidget != nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void ACurtainPlayerController::ShowRestartWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("ACurtainPlayerController"));

	if (BP_RestartWidget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowRestartWidget"));

		SetPause(true);
		SetInputMode(FInputModeUIOnly());

		bShowMouseCursor = true;

		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
}

void ACurtainPlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();

	SetPause(false);

	SetInputMode(FInputModeGameOnly());

	bShowMouseCursor = false;
}

void ACurtainPlayerController::UpdateHealthPercent(float HealthPercent)
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}