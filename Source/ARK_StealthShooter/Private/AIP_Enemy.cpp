// Fill out your copyright notice in the Description page of Project Settings.


#include "AIP_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAIP_Enemy::SetEnemyStatus(EAIP_EnemyStatus NewEnemyStatus)
{
	float Speed = EnemySpeedMap[NewEnemyStatus];
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	BP_SetEnemyStatus(NewEnemyStatus);
}
