// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"
#include "Components/AudioComponent.h"

AMusicManager::AMusicManager()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Music Component"));
}

void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

