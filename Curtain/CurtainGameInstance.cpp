// Fill out your copyright notice in the Description page of Project Settings.


#include "CurtainGameInstance.h"

UCurtainGameInstance::UCurtainGameInstance()
{
	XP = 100.0f;
}

void UCurtainGameInstance::SetXP(const float NewXP)
{
	XP = NewXP;
}

float UCurtainGameInstance::GetXP() const
{
	return XP;
}