// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIP_HealingArea.generated.h"

class UStaticMeshComponent;
class AAIP_BaseCharacter;

UCLASS()
class ARK_STEALTHSHOOTER_API AAIP_HealingArea : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIP_HealingArea();

protected:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* AreaMeshComponent;

protected:

	UPROPERTY(EditDefaultsOnly)
	float HealingAmount;

	UPROPERTY(EditDefaultsOnly)
	float CooldownTime;

	FTimerHandle TimerHandle_HandleCooldown;

public:

	UPROPERTY()
	uint8 bIsActive:1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Heal(AAIP_BaseCharacter* HealCharacter);

	UFUNCTION()
	void Reset();

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
