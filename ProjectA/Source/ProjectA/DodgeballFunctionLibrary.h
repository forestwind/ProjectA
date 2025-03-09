// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DodgeballFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UDodgeballFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static bool CanSeeActor(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoredActors = TArray<const AActor*>());
	static bool CanSeeActorSweep(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoredActors = TArray<const AActor*>());
};
