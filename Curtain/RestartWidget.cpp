// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "CurtainPlayerController.h"
#include "CurtainSaveGame.h"

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &URestartWidget::OnExitClicked);
	}
}

void URestartWidget::OnRestartClicked()
{
	// Load Game
	UCurtainSaveGame* SaveGame = NewObject<UCurtainSaveGame>(USaveGame::StaticClass());
	SaveGame->Load();

	ACurtainPlayerController* PlayerController = Cast<ACurtainPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		//PlayerController->HideRestartWidget();
	}

	// UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
	UGameplayStatics::OpenLevel(this, FName("ThirdPersonMap"));
}

void URestartWidget::OnExitClicked()
{
	// Save Game
	UCurtainSaveGame* SaveGame = NewObject<UCurtainSaveGame>(USaveGame::StaticClass());
	SaveGame->Save();

	UKismetSystemLibrary::QuitGame(GetWorld(),
		nullptr,
		EQuitPreference::Quit,
		true);
}