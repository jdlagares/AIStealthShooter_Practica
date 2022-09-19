// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIP_BaseCharacter.h"
#include "AIP_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API AAIP_PlayerCharacter : public AAIP_BaseCharacter
{
	GENERATED_BODY()

public:

	AAIP_PlayerCharacter();

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

protected:

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void StartCrouch();

	void EndCrouch();

	virtual FVector GetPawnViewLocation() const override;

public:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
