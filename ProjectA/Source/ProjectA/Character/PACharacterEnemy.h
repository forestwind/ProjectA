// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PACharacterBase.h"
#include "PACharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APACharacterEnemy : public APACharacterBase
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void LookAtActor(AActor* TargetActor);
	bool CanSeeActor(const AActor* TargetActor) const;
	bool CanSeeActorSweep(const AActor* TargetActor) const;
};
