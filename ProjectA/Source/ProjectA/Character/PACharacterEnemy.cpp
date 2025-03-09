// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterEnemy.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../Projectile/DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../DodgeballFunctionLibrary.h"

APACharacterEnemy::APACharacterEnemy()
{
	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("SightSource"));
	SightSource->SetupAttachment(RootComponent);
}

void APACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	bCanSeePlayer = LookAtActor(PlayerCharacter);

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

bool APACharacterEnemy::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr)
	{
		return false;
	}
	const TArray<const AActor*> IgnoredActors = { this, TargetActor };

	//if (UDodgeballFunctionLibrary::CanSeeActorSweep(GetWorld(), SightSource->GetComponentLocation(), TargetActor, IgnoredActors))
	if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(), SightSource->GetComponentLocation(),TargetActor, IgnoredActors))
	{
		FVector Start = SightSource->GetComponentLocation();
		FVector End = TargetActor->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start,End);
		SetActorRotation(LookAtRotation);

		return true;
	}

	return false;
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
