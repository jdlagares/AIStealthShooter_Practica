// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_HealthComponent.h"

// Sets default values for this component's properties
UAIP_HealthComponent::UAIP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100.0f;
	bDied = false;
}


// Called when the game starts
void UAIP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = DefaultHealth;

	AActor* ActorOwner = GetOwner();
	if (ActorOwner) {
		ActorOwner->OnTakeAnyDamage.AddDynamic(this, &UAIP_HealthComponent::ReceiveDamage);
	}
	
}

void UAIP_HealthComponent::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage<=0.0f) {
		return;
	}
	if (bDied) {
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);
	OnHealthChanged.Broadcast(this, CurrentHealth, -Damage, DamageType, InstigatedBy, DamageCauser);
	
	if (CurrentHealth==0.0f) {
		bDied = true;
		OnDeath.Broadcast(this, InstigatedBy, DamageCauser);
	}
}

void UAIP_HealthComponent::Kill(AController* InstigatedBy, AActor* DamageCauser)
{
	if (bDied) {
		return;
	}
	CurrentHealth = 0.0f;
	bDied = true;
	OnDeath.Broadcast(this, InstigatedBy, DamageCauser);
}

void UAIP_HealthComponent::Heal(const float HealAmount, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bDied) {
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, DefaultHealth);
	OnHealthChanged.Broadcast(this, CurrentHealth, HealAmount, nullptr, InstigatedBy, DamageCauser);

}

bool UAIP_HealthComponent::IsFriendly(const AActor* ActorA, const AActor* ActorB)
{
	if (ActorA==nullptr || ActorB == nullptr) {
		return true;
	}
	UAIP_HealthComponent* HealthCompA = ActorA->FindComponentByClass<UAIP_HealthComponent>();
	UAIP_HealthComponent* HealthCompB = ActorB->FindComponentByClass<UAIP_HealthComponent>();
	if (HealthCompA == nullptr || HealthCompB == nullptr) {
		return true;
	}
	return HealthCompA->TeamNumber == HealthCompB->TeamNumber;
}


