// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LookAtActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API ULookAtActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookAtActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	bool LookAtActor();

	AActor* TargetActor;
	bool bCanSeeTarget = false;

public:

	FORCEINLINE void SetTargetActor(AActor* NewTarget) { TargetActor = NewTarget; }
	FORCEINLINE bool CanSeeActor() const { return bCanSeeTarget; }
};
