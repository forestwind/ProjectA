// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"


bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoredActors)
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	FHitResult Hit;
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoredActors);

	World->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	DrawDebugLine(World, Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}

bool UDodgeballFunctionLibrary::CanSeeActorSweep(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoredActors)
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	FHitResult Hit;
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	FQuat Rotation = FQuat::Identity;
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.0f, 20.0f, 20.0f));
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoredActors);

	World->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape, QueryParams);

	return !Hit.bBlockingHit;
}
