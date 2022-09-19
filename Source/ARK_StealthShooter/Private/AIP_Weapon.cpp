// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_Weapon.h"
#include "Components/StaticMeshComponent.h"
#include <ARK_StealthShooter/ARK_StealthShooter.h>
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "AIP_BaseCharacter.h"

// Sets default values
AAIP_Weapon::AAIP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = WeaponMesh;
	ShootDistance = 10000.f;
	Damage = 20.0f;
	RoundsPerMinute = 600.0f;
	bDrawDebug=false;
	ShotVolume = 1.0f;
}

// Called when the game starts or when spawned
void AAIP_Weapon::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60.0f / RoundsPerMinute;
}

void AAIP_Weapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner) {
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShootDirection = EyeRotation.Vector();

		FVector TraceEnd = EyeLocation + (ShootDirection * ShootDistance);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FVector ImpactPoint= TraceEnd;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, WEAPON_COLLISION, QueryParams)) {
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShootDirection, Hit, MyOwner->GetInstigatorController(), MyOwner, DamageType);

			if (ImpactEffect) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}

			ImpactPoint = Hit.ImpactPoint;
		}

		FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
		if (bDrawDebug) {
			DrawDebugLine(GetWorld(), EyeLocation, ImpactPoint, FColor::White, false, 1.0f, 0.0f, 1.0f);
		}

		if (MuzzleEffect) {
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMesh, MuzzleSocketName);
		}

		if (ShotSound) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSound, MuzzleLocation, ShotVolume);
		}

		if (TracerEffect) {
			FVector MuzzleSocketLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
			UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleSocketLocation);
			if (TracerComponent) {
				TracerComponent->SetVectorParameter(TracerName, ImpactPoint);
			}
		}

		AAIP_BaseCharacter* OwnerCharacter = Cast<AAIP_BaseCharacter>(MyOwner);
		if(OwnerCharacter){
			OwnerCharacter->CharacterMakeNoise(ShotLoudness, MuzzleLocation);
		}

		LastFireTime = GetWorld()->TimeSeconds;

	}
}

// Called every frame
void AAIP_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIP_Weapon::StartFire()
{
	float firstDelay = FMath::Max(0.0f, LastFireTime + TimeBetweenShots-GetWorld()->TimeSeconds);
	GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AAIP_Weapon::Fire, TimeBetweenShots, true, firstDelay);
}

void AAIP_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(AutoFireTimer);
}

