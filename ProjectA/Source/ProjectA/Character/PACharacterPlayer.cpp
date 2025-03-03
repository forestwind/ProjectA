// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"

APACharacterPlayer::APACharacterPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// 컨트롤러가 회전할 때 캐릭터가 회전하지 않도록 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 캐릭터 회전

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; // 카메라 회전은 컨트롤러에 의해 제어

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // 컨트롤러에 의해 카메라 회전하지 않음
}

void APACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedPlayerInputComponent != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			if (EnhancedSubsystem != nullptr)
			{
				EnhancedSubsystem->AddMappingContext(IC_Character, 1);
			}
		}

		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APACharacterPlayer::Move);
		EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APACharacterPlayer::Look);
		EnhancedPlayerInputComponent->BindAction(IA_Walk, ETriggerEvent::Started, this, &APACharacterPlayer::BeginWalking);
		EnhancedPlayerInputComponent->BindAction(IA_Walk, ETriggerEvent::Completed, this, &APACharacterPlayer::StopWalking);
	}
}

void APACharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2d>();
	if(Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f))
	{
		const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (InputValue.X != 0.0f)
		{
			const FVector RightDirection = UKismetMathLibrary::GetRightVector(YawRotation);
			AddMovementInput(RightDirection, InputValue.X);
		}

		if (InputValue.Y != 0.0f)
		{
			//const FVector ForwardDirection = YawRotation.Vector();
			const FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(YawRotation);
			AddMovementInput(ForwardDirection, InputValue.Y);
		}
	}
}

void APACharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2d>();
	
	if (InputValue.X != 0.0f)
	{
		AddControllerYawInput(InputValue.X);
	}

	if (InputValue.Y != 0.0f)
	{
		AddControllerPitchInput(InputValue.Y);
	}
}

void APACharacterPlayer::BeginWalking()
{
	GetCharacterMovement()->MaxWalkSpeed *= 0.4f;
}

void APACharacterPlayer::StopWalking()
{
	GetCharacterMovement()->MaxWalkSpeed /= 0.4f;
}
