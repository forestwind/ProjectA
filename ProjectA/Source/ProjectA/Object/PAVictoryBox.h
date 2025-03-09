// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PAVictoryBox.generated.h"

UCLASS()
class PROJECTA_API APAVictoryBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APAVictoryBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VictoryBox, Meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VictoryBox, Meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

public:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
