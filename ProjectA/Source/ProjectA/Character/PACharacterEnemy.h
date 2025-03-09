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
	APACharacterEnemy();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool LookAtActor(AActor* TargetActor);
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, Meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SightSource;

protected:
	bool bCanSeePlayer = false;
	bool bPreviousCanSeePlayer = false;
	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval = 2.0f;
	float ThrowingDelay = 0.5f;

	void ThrowDodgeball();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
	TSubclassOf<class ADodgeballProjectile> DodgeballClass;
};
