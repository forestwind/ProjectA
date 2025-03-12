// Fill out your copyright notice in the Description page of Project Settings.


#include "PAPlayerController.h"
#include "Widget/RestartWidget.h"

void APAPlayerController::ShowRestartWidget()
{
	if (BP_RestartWidget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
}

void APAPlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromViewport();
	RestartWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
