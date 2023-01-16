// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Enemy.h"
#include "RedPlayer.h"
#include <Kismet/GameplayStatics.h>


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

	// 월드에서 ARedPlayer 타깃 찾기
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass());
	// ARedPlayer 타입으로 캐스팅
	target = Cast<ARedPlayer>(actor);
	// 소유 객체 가져오기
	me = Cast<AEnemy>(GetOwner());
	
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
	// 1.시간이 흘렀으니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2.시간이 경과했는지 확인
	if (currentTime > IdleDelayTime)
	{
		// 3.상태를 이동 상태로 변경
		mState = EEnemyState::Move;
		// 4.경과 시간 초기화
		currentTime = 0.0f;
	}
}
// 이동 상태
void UEnemyFSM::MoveState()
{
	// 1. 타깃 목적지가 필요함.
	FVector destination = target->GetActorLocation();
	// 2. 방향이 필요함.
	FVector direction = destination - me->GetActorLocation();
	// 3. 방향으로 이동하고 싶다.
	me->AddMovementInput(direction.GetSafeNormal());
	
	// 타깃과 가까워 지면 공격 상태로 전환하고 싶다.
	// 1. 만약 거리가 공격 범위 안에 들어오면..
	if (direction.Size() < AttackRange)
	{
		// 2. 상태를 공격 상태로 변경
		mState = EEnemyState::Attack;
	}
}
// 공격 상태
void UEnemyFSM::AttackState()
{
	// 목표 : 일정시간 마다 한번씩 공격하고싶다.
	// 1. 시간이 흘렀으니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. 공격시간이 경과했는지 확인
	if (currentTime > AttackDelayTime)
	{
		// 3. 공격
		UE_LOG(LogTemp, Warning, TEXT("DIE!!"));
		// 4. 경과 시간 초기화
		currentTime = 0.0f;
		
		// 목표 : 타깃이 공격 범위를 벗어나면 상태를 이동으로 전환하고 싶다.
		// 1. 타깃과의 거리가 필요하다.
		float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
		// 2. 만약 거리가 공격 범위보다 크면
		if (distance > AttackRange)
		{
			// 3. 상태를 이동 상태로 변경
			mState = EEnemyState::Move;
		}
	}

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

void UEnemyFSM::OnDamageProcess()
{
	me->Destroy();
}
