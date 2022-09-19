// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AIP_Weapon.h"
#include "AIP_HealthComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PawnNoiseEmitterComponent.h"

// Sets default values
AAIP_BaseCharacter::AAIP_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	bIsMeleeAttacking=false;
	HealthComponent = CreateDefaultSubobject<UAIP_HealthComponent>(TEXT("HealthComponent"));
	CharacterNoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComponent"));
	CharacterNoiseEmitter->SetAutoActivate(true);
}

// Called when the game starts or when spawned
void AAIP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (StartingWeaponClass) {
		CurrentWeapon = GetWorld()->SpawnActor<AAIP_Weapon>(StartingWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (CurrentWeapon) {
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
		}
	}
	if (MeleeAttackMontage) {
		AnimBp = GetMesh()->GetAnimInstance();
		if (AnimBp) {
			AnimBp->OnMontageEnded.AddDynamic(this, &AAIP_BaseCharacter::StopMelee);
		}
	}
	if (HealthComponent) {
		HealthComponent->OnHealthChanged.AddDynamic(this, &AAIP_BaseCharacter::OnHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &AAIP_BaseCharacter::OnDeath);
	}
}

void AAIP_BaseCharacter::StartMelee()
{
	if (bIsMeleeAttacking) {
		return;
	}
	if (AnimBp) {
		if (bIsShoting) {
			StopFire();
		}
		bIsMeleeAttacking = true;
		AnimBp->Montage_Play(MeleeAttackMontage);
	}
}

void AAIP_BaseCharacter::StopMelee(UAnimMontage* Anim, bool bIsInterrupted)
{
	if (Anim==MeleeAttackMontage) {
		bIsMeleeAttacking = false;
	}
}

void AAIP_BaseCharacter::DoMeleeAttack()
{
	const FVector MeleeAttackLocation = GetMesh()->GetSocketLocation(MeleeAttackBoneName);

	TArray<AActor*>ActorsToIngnore;
	ActorsToIngnore.Add(this);

	TArray<AActor*> OutActors;

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), MeleeAttackLocation, MeleeAttackRange, ObjectTypes, AActor::StaticClass(), ActorsToIngnore, OutActors)) {
		AActor* HitActor = OutActors[0];
		if (HitActor) {
			UAIP_HealthComponent* HitActorHealthComp = Cast<UAIP_HealthComponent>(HitActor->GetComponentByClass(UAIP_HealthComponent::StaticClass()));
			if (HitActorHealthComp) {
				HitActorHealthComp->Kill(GetController(), this);
			}
		}
	};
}

void AAIP_BaseCharacter::Startfire()
{
	if (bIsMeleeAttacking) {
		return;
	}
	if (CurrentWeapon) {
		bIsShoting = true;
		CurrentWeapon->StartFire();
	}
}

void AAIP_BaseCharacter::StopFire()
{
	if (CurrentWeapon) {
		bIsShoting = false;
		CurrentWeapon->StopFire();
	}
}

void AAIP_BaseCharacter::OnHealthChanged(UAIP_HealthComponent* HealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

}

void AAIP_BaseCharacter::OnDeath(UAIP_HealthComponent* HealthComp, AController* InstigatedBy, AActor* Killer)
{
	StopFire();
	GetMovementComponent()->StopMovementImmediately();
	this->SetActorEnableCollision(false);

}

void AAIP_BaseCharacter::CharacterMakeNoise(float Loudness, const FVector& NoiseLocation)
{
	if (CharacterNoiseEmitter) {
		CharacterNoiseEmitter->MakeNoise(this, Loudness,NoiseLocation);
	}
}


// Called every frame
void AAIP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAIP_HealthComponent* AAIP_BaseCharacter::GetHealthComponent()
{
	return HealthComponent;
}


