// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CurtainProjectile.h"

#include "CurtainEnemyCharacter.generated.h"

UCLASS()
class CURTAIN_API ACurtainEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACurtainEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool LookAtActor(AActor* TargetActor);
	bool CanSeeActor(const AActor* TargetActor) const;
	void ThrowBall();

public:
	bool bCanSeePlayer;
	bool bPreviousCanSeePlayer;
	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval{ 2.0f };
	float ThrowingDelay{ 0.5f };


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
		USceneComponent* SightSource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<ACurtainProjectile> ProjectileClass;
};
