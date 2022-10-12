// Fill out your copyright notice in the Description page of Project Settings.


#include "CurtainEnemyCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "CurtainGameInstance.h"

// Sets default values
ACurtainEnemyCharacter::ACurtainEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("SightSouce"));
	SightSource->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACurtainEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Get GameInstance Level Info
	UCurtainGameInstance* CurtainGameInstance = Cast<UCurtainGameInstance>(GetGameInstance());
	float CurrentXPInLevel = CurtainGameInstance->GetXP();
	UE_LOG(LogTemp, Warning, TEXT("Current XP in Level : %f"), CurrentXPInLevel);
}

// Called every frame
void ACurtainEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	bCanSeePlayer = LookAtActor(PlayerCharacter);
	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		//if (bCanSeePlayer)
		//{
		//	// start throwing
		//	GetWorldTimerManager().SetTimer(ThrowTimerHandle,
		//		this,
		//		&ACurtainEnemyCharacter::ThrowBall,
		//		ThrowingInterval,
		//		true,
		//		ThrowingDelay);
		//}
		//else
		//{
		//	// stop Throwing
		//	GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		//}

	}
	bPreviousCanSeePlayer = bCanSeePlayer;
}

// Called to bind functionality to input
void ACurtainEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ACurtainEnemyCharacter::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr) return false;

	if (CanSeeActor(TargetActor))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		// Set Enemy Actor Rotation
		SetActorRotation(Rotation);

		return true;
	}

	return false;
}

bool ACurtainEnemyCharacter::CanSeeActor(const AActor* TargetActor) const
{
	if (TargetActor == nullptr) return false;

	FHitResult HitResult;
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	ECollisionChannel CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(TargetActor);

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, CollisionChannel, QueryParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	// If there is a blocking hit, we can't see our TargetActor
	return !HitResult.bBlockingHit;
}

void ACurtainEnemyCharacter::ThrowBall()
{
	UE_LOG(LogTemp, Warning, TEXT("Throwing ..."));

	if (ProjectileClass == nullptr) return;

	// unitary fector: actor facing direction 
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 100.0f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);

	ACurtainProjectile* Projectile = GetWorld()->SpawnActor<ACurtainProjectile>(ProjectileClass, SpawnLocation, GetActorRotation());
	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.f;
}
