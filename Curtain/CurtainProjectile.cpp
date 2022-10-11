// Fill out your copyright notice in the Description page of Project Settings.


#include "CurtainProjectile.h"
#include "CurtainCharacter.h"
#include "HealthComponent.h"

// Sets default values
ACurtainProjectile::ACurtainProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(45.f);
	SphereComponent->SetCollisionProfileName(FName("Projectile"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &ACurtainProjectile::OnHit);

	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1500.f;
}

// Called when the game starts or when spawned
void ACurtainProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Set Life Span
	SetLifeSpan(5.0f);
}

// Called every frame
void ACurtainProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACurtainProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ACurtainCharacter* Player = Cast<ACurtainCharacter>(OtherActor);
	if (Player != nullptr)
	{
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
		if (HealthComponent != nullptr)
		{
			HealthComponent->LoseHealth(Damage);
		}
	}

}


