// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIP_BaseCharacter.generated.h"

class AAIP_Weapon;
class UAIP_HealthComponent;
class UPawnNoiseEmitterComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API AAIP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIP_BaseCharacter();

public:

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsMeleeAttacking;

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAIP_Weapon> StartingWeaponClass;

	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName;

	UPROPERTY(BlueprintReadOnly)
	AAIP_Weapon* CurrentWeapon; 

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAIP_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnNoiseEmitterComponent* CharacterNoiseEmitter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly ,Category ="Melee")
	UAnimMontage* MeleeAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeAttackBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeAttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(BlueprintReadOnly)
	bool bIsShoting;

	UAnimInstance* AnimBp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartMelee();

	UFUNCTION(BlueprintCallable)
	void StopMelee(UAnimMontage* Anim, bool bIsInterrupted);

	UFUNCTION(BlueprintCallable)
	void DoMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void Startfire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION()
	void OnHealthChanged(UAIP_HealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnDeath(UAIP_HealthComponent* HealthComp, class AController* InstigatedBy, AActor* Killer);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UAIP_HealthComponent* GetHealthComponent();

	UFUNCTION()
	void CharacterMakeNoise(float Loudness, const FVector& NoiseLocation);

};
