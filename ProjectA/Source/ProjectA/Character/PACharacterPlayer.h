// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PACharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PACharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APACharacterPlayer : public APACharacterBase
{
	GENERATED_BODY()
	
public:

	APACharacterPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyTPS_Cam", meta = (AllowPrivateAccess ="true"))
    USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyTPS_Cam", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
};
