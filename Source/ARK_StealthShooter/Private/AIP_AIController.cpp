// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_AIController.h"
#include "AIP_HealthComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

AAIP_AIController::AAIP_AIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))) {
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AAIP_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const AActor* OtherActor = &Other;
	return (UAIP_HealthComponent::IsFriendly(GetPawn(), OtherActor)) ? ETeamAttitude::Friendly: ETeamAttitude::Hostile;

}
