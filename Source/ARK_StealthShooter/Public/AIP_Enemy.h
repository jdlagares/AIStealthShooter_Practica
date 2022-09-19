// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIP_BaseCharacter.h"
#include "AIP_Enemy.generated.h"


UENUM(BlueprintType)
enum class EAIP_EnemyStatus : uint8 {
	EnemyStatus_Patrol=0		UMETA(DisplayName=Patrol),
	EnemyStatus_Finding = 1		UMETA(DisplayName = Seek),
	EnemyStatus_Combat = 2		UMETA(DisplayName = Combat)

};

class AAIP_PatrolActor;
/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API AAIP_Enemy : public AAIP_BaseCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AAIP_PatrolActor* PatrolActorReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EAIP_EnemyStatus, float> EnemySpeedMap;

	UFUNCTION(BlueprintCallable)
	void SetEnemyStatus(EAIP_EnemyStatus NewEnemyStatus);


protected:

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SetEnemyStatus(EAIP_EnemyStatus NewEnemyStatus);
};
