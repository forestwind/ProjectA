// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterEnemy.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void APACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActor(PlayerCharacter);
}

void APACharacterEnemy::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr)
	{
		return;
	}
	
	if (CanSeeActor(TargetActor))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start,End);
		SetActorRotation(LookAtRotation);
	}
}

bool APACharacterEnemy::CanSeeActor(const AActor* TargetActor) const
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
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
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.0f, 20.0f, 20.0f));

	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);

	return !Hit.bBlockingHit;
}
