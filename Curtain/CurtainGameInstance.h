// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CurtainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CURTAIN_API UCurtainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCurtainGameInstance();
	
public:
	void SetXP(const float NewXP);
	float GetXP() const;
private:
	float XP;
};
