// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIP_PatrolActor.generated.h"

class USplineComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API AAIP_PatrolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIP_PatrolActor();

	USplineComponent* SplineComponent;

	UFUNCTION(BlueprintCallable)
	FVector GetWorldLocationByIndex(const int32 Index) const;

	UFUNCTION(BlueprintCallable)
	int32 GetLastIndex() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
