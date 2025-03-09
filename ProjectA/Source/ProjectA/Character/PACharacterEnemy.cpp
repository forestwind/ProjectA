// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterEnemy.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../Projectile/DodgeballProjectile.h"

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
	
	if (CanSeeActor(TargetActor))
	{
		FVector Start = SightSource->GetComponentLocation();
		FVector End = TargetActor->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start,End);
		SetActorRotation(LookAtRotation);

		return true;
	}

	return false;
}

bool APACharacterEnemy::CanSeeActor(const AActor* TargetActor) const
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	FHitResult Hit;
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(TargetActor);
	
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}

bool APACharacterEnemy::CanSeeActorSweep(const AActor* TargetActor) const
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	FQuat Rotation = FQuat::Identity;
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.0f, 20.0f, 20.0f));

	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);

	return !Hit.bBlockingHit;
}

void APACharacterEnemy::ThrowDodgeball()
{
	if (DodgeballClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.0f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	GetWorld()->SpawnActor<ADodgeballProjectile>(DodgeballClass, SpawnLocation, GetActorRotation());
	
}
