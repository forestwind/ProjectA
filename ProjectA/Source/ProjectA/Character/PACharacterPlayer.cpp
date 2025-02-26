// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

APACharacterPlayer::APACharacterPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// ��Ʈ�ѷ��� ȸ���� �� ĳ���Ͱ� ȸ������ �ʵ��� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // �̵� �������� ĳ���� ȸ��

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; // ī�޶� ȸ���� ��Ʈ�ѷ��� ���� ����

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // ��Ʈ�ѷ��� ���� ī�޶� ȸ������ ����
}