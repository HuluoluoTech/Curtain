// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CurtainSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CURTAIN_API UCurtainSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UCurtainSaveGame();

public:
	void Save();
	void Load();

	void SaveGameDelegate(const FString& SlotName, int32 UserIndex, bool bSuccess);
	void LoadGameDelegate(const FString& SlotName, int32 UserIndex, USaveGame* LoadedGameData);
	
public:
	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		FString PlayerName;
	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		int Level;
	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		float Health;
	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		FString SaveSlotName;
	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		uint32 UserIndex;

};
