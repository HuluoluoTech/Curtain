// Fill out your copyright notice in the Description page of Project Settings.


#include "CurtainWall.h"

// Sets default values
ACurtainWall::ACurtainWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = RootScene;
}

// Called when the game starts or when spawned
void ACurtainWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACurtainWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

