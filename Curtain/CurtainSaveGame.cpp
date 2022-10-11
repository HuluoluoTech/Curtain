// Fill out your copyright notice in the Description page of Project Settings.


#include "CurtainSaveGame.h"
#include "Kismet/GameplayStatics.h"

UCurtainSaveGame::UCurtainSaveGame()
{
	SaveSlotName = TEXT("SaveSlotName");
	UserIndex = 0;
}

void UCurtainSaveGame::Save()
{
	if (UCurtainSaveGame* SaveGameInstance = Cast<UCurtainSaveGame>(UGameplayStatics::CreateSaveGameObject(UCurtainSaveGame::StaticClass())))
	{
		FAsyncSaveGameToSlotDelegate Delegate;
		Delegate.BindUObject(this, &UCurtainSaveGame::SaveGameDelegate);

		SaveGameInstance->PlayerName = TEXT("zTgx");
		SaveGameInstance->Level = 2;
		SaveGameInstance->Health = 0.8f;

		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex, Delegate);
	}
}

void UCurtainSaveGame::Load()
{
	FAsyncLoadGameFromSlotDelegate Delegate;
	Delegate.BindUObject(this, &UCurtainSaveGame::LoadGameDelegate);

	UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, UserIndex, Delegate);
}

void UCurtainSaveGame::SaveGameDelegate(const FString& SlotName, int32 Index, bool bSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Save Result: %d"), bSuccess);


}

void UCurtainSaveGame::LoadGameDelegate(const FString& SlotName, int32 Index, USaveGame* LoadedGameData)
{
	if (UCurtainSaveGame* SaveGame = Cast<UCurtainSaveGame>(LoadedGameData))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerName : %s"), *SaveGame->PlayerName);
	}
}
