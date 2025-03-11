// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterEnemy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../Projectile/DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Component/LookAtActorComponent.h"

APACharacterEnemy::APACharacterEnemy()
{
	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("LookAtActorComponent"));
	LookAtActorComponent->SetupAttachment(RootComponent);
}

void APACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTargetActor(PlayerCharacter);
}

void APACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	bCanSeePlayer = LookAtActorComponent->CanSeeActor();

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			//UE_LOG(LogTemp, Warning, TEXT("I can see the player"));
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &APACharacterEnemy::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);

		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
			//UE_LOG(LogTemp, Warning, TEXT("I can't see the player"));
		}
	}


	bPreviousCanSeePlayer = bCanSeePlayer;
}

void APACharacterEnemy::ThrowDodgeball()
{
	if (DodgeballClass == nullptr)
	{
		return;
	}

	// ÀÏ¹Ý Spawn 
	/*
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.0f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	GetWorld()->SpawnActor<ADodgeballProjectile>(DodgeballClass, SpawnLocation, GetActorRotation());
	*/

	// Deferred Spawn
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.0f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform = FTransform(GetActorRotation(), SpawnLocation);
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.0f;
	Projectile->FinishSpawning(SpawnTransform);
}
