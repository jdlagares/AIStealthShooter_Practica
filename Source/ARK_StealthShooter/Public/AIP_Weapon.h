// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIP_Weapon.generated.h"

class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class ARK_STEALTHSHOOTER_API AAIP_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIP_Weapon();

protected:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* WeaponMesh;

protected:

	UPROPERTY(EditDefaultsOnly)
	float ShootDistance;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly,meta=(ClampMin=0.1f))
	float RoundsPerMinute;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebug;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly)
	FName TracerName;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ShotSound;

	UPROPERTY(EditDefaultsOnly)
	float ShotVolume;

	UPROPERTY(EditDefaultsOnly)
	float ShotLoudness;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactEffect;

	FTimerHandle AutoFireTimer;

	float TimeBetweenShots;

	float LastFireTime;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartFire();

	void StopFire();
};
