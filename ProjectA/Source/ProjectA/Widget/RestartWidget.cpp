// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "../PAPlayerController.h"

void URestartWidget::OnRestartButtonClicked()
{
	APAPlayerController* PlayerController = Cast<APAPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideRestartWidget();
	}


	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartButtonClicked);
	}
	
}
