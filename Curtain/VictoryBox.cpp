// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CurtainCharacter.h"


// Sets default values
AVictoryBox::AVictoryBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(60.0, 60.0f, 60.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0, 0.0f, 120.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AVictoryBox::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AVictoryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVictoryBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVictoryBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("AVictoryBox -> OnBeginOverlap..."));

	if (Cast<ACurtainCharacter>(OtherActor))
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),
			nullptr,
			EQuitPreference::Quit,
			true);
	}
}

