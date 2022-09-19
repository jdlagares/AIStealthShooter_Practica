// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_HealingArea.h"
#include "AIP_HealthComponent.h"
#include "AIP_BaseCharacter.h"

// Sets default values
AAIP_HealingArea::AAIP_HealingArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AreaMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealingArea"));
	SetRootComponent(AreaMeshComponent);

	bIsActive = true;

}

// Called when the game starts or when spawned
void AAIP_HealingArea::BeginPlay()
{
	Super::BeginPlay();
	if (AreaMeshComponent) {
		AreaMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AAIP_HealingArea::OnOverlap);
	}
}

void AAIP_HealingArea::Heal(AAIP_BaseCharacter* HealCharacter)
{
	UAIP_HealthComponent* HealthComp = HealCharacter->GetHealthComponent();
	if (HealthComp) {
		HealthComp->Heal(HealingAmount,nullptr,this);
	}
	bIsActive = false;
	AreaMeshComponent->SetVisibility(false);
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().SetTimer(TimerHandle_HandleCooldown,this,&AAIP_HealingArea::Reset,CooldownTime);
}

void AAIP_HealingArea::Reset()
{
	bIsActive = true;
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AreaMeshComponent->SetVisibility(true);
}

void AAIP_HealingArea::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAIP_BaseCharacter* OverlappingActor = Cast<AAIP_BaseCharacter>(OtherActor);
	if (OverlappingActor) {
		Heal(OverlappingActor);
	}
}


