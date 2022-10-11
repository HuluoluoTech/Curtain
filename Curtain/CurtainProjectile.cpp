// Fill out your copyright notice in the Description page of Project Settings.


#include "CurtainProjectile.h"
#include "CurtainCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

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
	SetLifeSpan(2.0f);
}

// Called every frame
void ACurtainProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACurtainProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// NormalImpulse
	// : the direction and magnitude


	ACurtainCharacter* Player = Cast<ACurtainCharacter>(OtherActor);
	if (Player != nullptr)
	{
		if (BounceSound != nullptr && NormalImpulse.Size() > 600.0f)
		{
			UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation(), 1.0f, FMath::RandRange(0.7f, 1.3f));
		}

		// Particle
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorTransform());

		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
		if (HealthComponent != nullptr)
		{
			HealthComponent->LoseHealth(Damage);
		}
	}

}


