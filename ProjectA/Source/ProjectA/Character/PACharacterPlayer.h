// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PACharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess ="true"))
    USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IC_Character;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_ShoulderLook;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_ShoulderMove;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_QuaterMove;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_ChangeControlView;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Jump;

	
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Walk;

protected:

	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);

	void QuaterMove(const FInputActionValue& Value);

	void BeginWalking();
	void StopWalking();

	ECharacterControlType CurrentCharacterControlType;

protected:
	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class UPACharacterControlData* CharacterControlData) override;
};
