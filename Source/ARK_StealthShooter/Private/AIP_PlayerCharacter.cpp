// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAIP_PlayerCharacter::AAIP_PlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AAIP_PlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AAIP_PlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AAIP_PlayerCharacter::StartCrouch()
{
	Crouch();
}

void AAIP_PlayerCharacter::EndCrouch()
{
	UnCrouch();
}

FVector AAIP_PlayerCharacter::GetPawnViewLocation() const
{
	if (Camera) {
		return Camera->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

void AAIP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//mirar hacia los lados
	PlayerInputComponent->BindAxis("LookUp", this, &AAIP_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookSide", this, &AAIP_PlayerCharacter::AddControllerYawInput);

	//caminar
	PlayerInputComponent->BindAxis("MoveForward", this, &AAIP_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAIP_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AAIP_PlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AAIP_PlayerCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAIP_PlayerCharacter::Startfire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AAIP_PlayerCharacter::StopFire);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AAIP_PlayerCharacter::StartMelee);
}
