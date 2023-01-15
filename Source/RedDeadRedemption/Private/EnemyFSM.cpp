// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	{
		switch (mState)
		{
		case EEnemyState::Idle:
			IdleState();
			break;
		case EEnemyState::Move:
			MoveState();
			break;
		case EEnemyState::Attack:
			AttackState();
			break;
		case EEnemyState::Damage:
			DamageState();
			break;
		case EEnemyState::Dead:
			DeadState();
			break;
		}
	}
}

// 대기 상태
void UEnemyFSM::IdleState()
{
	// 대기 상태에서는 아무것도 하지 않는다.
}
// 이동 상태
void UEnemyFSM::MoveState()
{
	// 이동 상태에서는 아무것도 하지 않는다.
}
// 공격 상태
void UEnemyFSM::AttackState()
{
	// 공격 상태에서는 아무것도 하지 않는다.
}
// 피격 상태
void UEnemyFSM::DamageState()
{
	// 피격 상태에서는 아무것도 하지 않는다.
}
// 사망 상태
void UEnemyFSM::DeadState()
{
	// 사망 상태에서는 아무것도 하지 않는다.
}
