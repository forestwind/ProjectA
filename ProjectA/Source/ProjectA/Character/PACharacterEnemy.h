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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, Meta = (AllowPrivateAccess = "true"))
	class ULookAtActorComponent* LookAtActorComponent;

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
