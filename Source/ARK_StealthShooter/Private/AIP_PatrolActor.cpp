// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_PatrolActor.h"
#include "Components/SplineComponent.h"
// Sets default values
AAIP_PatrolActor::AAIP_PatrolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

FVector AAIP_PatrolActor::GetWorldLocationByIndex(const int32 Index) const
{
	if (SplineComponent && Index<= GetLastIndex()) {
		return SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	}
	return GetActorLocation();
}

int32 AAIP_PatrolActor::GetLastIndex() const
{
	if (SplineComponent) {
		return SplineComponent->GetNumberOfSplinePoints();
	}
	return 0;
}

// Called when the game starts or when spawned
void AAIP_PatrolActor::BeginPlay()
{
	Super::BeginPlay();
	
}



