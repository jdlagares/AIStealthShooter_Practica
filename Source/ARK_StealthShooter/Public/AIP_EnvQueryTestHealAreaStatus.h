// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "AIP_EnvQueryTestHealAreaStatus.generated.h"

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API UAIP_EnvQueryTestHealAreaStatus : public UEnvQueryTest
{
	GENERATED_BODY()

public:

	UAIP_EnvQueryTestHealAreaStatus(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
	
};
