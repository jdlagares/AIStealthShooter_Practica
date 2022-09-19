// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_EnvQueryTestHealAreaStatus.h"
#include "AIP_HealingArea.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

UAIP_EnvQueryTestHealAreaStatus::UAIP_EnvQueryTestHealAreaStatus(const FObjectInitializer& ObjectInitializer)
{
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();
}

void UAIP_EnvQueryTestHealAreaStatus::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It) {
		AAIP_HealingArea* HealingArea = Cast<AAIP_HealingArea>(GetItemActor(QueryInstance,It.GetIndex()));
		float Score = 0.0f;
		if (HealingArea) {
			Score = HealingArea->bIsActive ? 1.0 : 0.0f;
			It.SetScore(TestPurpose,FilterType, Score,0.0f,1.0f);
			It.ForceItemState(HealingArea->bIsActive ? EEnvItemStatus::Passed : EEnvItemStatus::Failed);
		}
	}
}

FText UAIP_EnvQueryTestHealAreaStatus::GetDescriptionTitle() const
{
	FString DescriptionTitle = "Testing for Healing Area status";
	return FText().FromString(DescriptionTitle);
}

FText UAIP_EnvQueryTestHealAreaStatus::GetDescriptionDetails() const
{
	FString DescriptionTitle = "Score when active:1, Score when inactive:0 ";
	return FText().FromString(DescriptionTitle);
}
