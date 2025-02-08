// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyrusGameProjectile.h"
#include "CustomMeshActor.h"
#include "CyrusGameCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

ACyrusGameProjectile::ACyrusGameProjectile() 
{
	PrimaryActorTick.bCanEverTick = false;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACyrusGameProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ACyrusGameProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ACyrusGameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and if we hit a physics body
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 75.0f, GetActorLocation());
	}

	if (OtherActor)
	{
		ACustomMeshActor* HitBox = Cast<ACustomMeshActor>(OtherActor);
		if (HitBox)
		{
			// ✅ Get the Player Character
			ACyrusGameCharacter* Player = Cast<ACyrusGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			if (Player)
			{
				// ✅ Add the box's score to the player's score
				Player->AddScore(HitBox->ScorePoints);
			}

			// ✅ Destroy the box
			HitBox->TakeDamage();
		}

		// ✅ Destroy the projectile
		Destroy();
	}
}