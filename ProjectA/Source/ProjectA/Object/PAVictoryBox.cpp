// Fill out your copyright notice in the Description page of Project Settings.


#include "PAVictoryBox.h"
#include "Components/BoxComponent.h"
#include "../Character/PACharacterPlayer.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APAVictoryBox::APAVictoryBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APAVictoryBox::OnBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APAVictoryBox::OnEndOverlap);
}

// Called when the game starts or when spawned
void APAVictoryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APAVictoryBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APAVictoryBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player has OnBeginOverlap"));

	if (Cast<APACharacterPlayer>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has entered the victory box"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
	}
}

void APAVictoryBox::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

