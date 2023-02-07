// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "Enemy.h"

void UEnemyAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	me = Cast<AEnemy>(TryGetPawnOwner());
}


void UEnemyAnim::AnimNotify_OnHit()
{
	if (this == nullptr)
	{
		return;
	}
}

void UEnemyAnim::AnimNotify_OnAttack()	
{
	if (this == nullptr)
	{
		return;
	}
	me->myEnemyFSM->OnAttackEvent();
}
