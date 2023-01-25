// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Enemy.h"
#include "RedPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include	"EnemyAI.h"

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

	// ���忡�� ARedPlayer Ÿ�� ã��
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass());
	// ARedPlayer Ÿ������ ĳ����
	target = Cast<ARedPlayer>(actor);
	// ���� ��ü ��������
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

// ��� ����
void UEnemyFSM::IdleState()
{
	// ���� �÷��̾� �������� ����
	FCollisionShape shape;
	shape.SetSphere(3000.0f);
	// ���� ��ġ
	FVector location = me->GetActorLocation();
	// ���� ��ġ���� �÷��̾� �������� ����
	TArray<FHitResult> hits;
	// ���� ��ġ���� �÷��̾� �������� ����
	GetWorld()->SweepMultiByChannel(hits, location, location, FQuat::Identity, ECollisionChannel::ECC_Pawn, shape);
	// �÷��̾ ���������� ������
	for (auto hit : hits)
	{
		// �÷��̾� Ÿ������ ĳ����
		auto player = Cast<ARedPlayer>(hit.GetActor());
		// �÷��̾ �����ϸ�
		if (player)
		{
			// �÷��̾ Ÿ������ ����
			target = player;
			// ���¸� �̵� ���·� ����
			mState = EEnemyState::Move;
			// �ݺ��� ����
			break;
		}
	}	
	
	// 1.�ð��� �귶���ϱ�
	//currentTime += GetWorld()->DeltaTimeSeconds;
	// 2.�ð��� ����ߴ��� Ȯ��
	//if (currentTime > IdleDelayTime)
	//{
	//	// 3.���¸� �̵� ���·� ����
	//	mState = EEnemyState::Move;
	//	// 4.��� �ð� �ʱ�ȭ
	//	currentTime = 0.0f;
	//}
}
// �̵� ����
void UEnemyFSM::MoveState()
{
	// 1. Ÿ�� �������� �ʿ���.
	FVector destination = target->GetActorLocation();
	// 2. ������ �ʿ���.
	FVector direction = destination - me->GetActorLocation();
	// 3. �������� �̵��ϰ� �ʹ�.

	me->AddMovementInput(direction.GetSafeNormal());

	
	// Ÿ��� ����� ���� ���� ���·� ��ȯ�ϰ� �ʹ�.
	// 1. ���� �Ÿ��� ���� ���� �ȿ� ������..
	if (direction.Size() < AttackRange)
	{
		// 2. ���¸� ���� ���·� ����
		mState = EEnemyState::Attack;
	}
}
// ���� ����
void UEnemyFSM::AttackState()
{
	// ��ǥ : �����ð� ���� �ѹ��� �����ϰ��ʹ�.
	// 1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. ���ݽð��� ����ߴ��� Ȯ��
	if (currentTime > AttackDelayTime)
	{
		// 3. ����
		//UE_LOG(LogTemp, Warning, TEXT("DIE!!"));
		// 4. ��� �ð� �ʱ�ȭ
		currentTime = 0.0f;
		
		// ��ǥ : Ÿ���� ���� ������ ����� ���¸� �̵����� ��ȯ�ϰ� �ʹ�.
		// 1. Ÿ����� �Ÿ��� �ʿ��ϴ�.
		float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
		// 2. ���� �Ÿ��� ���� �������� ũ��
		if (distance > AttackRange)
		{
			// 3. ���¸� �̵� ���·� ����
			mState = EEnemyState::Move;
		}
	}

}
// �ǰ� ����
void UEnemyFSM::DamageState()
{
	// �ǰ� ���¿����� �ƹ��͵� ���� �ʴ´�.
}
// ��� ����
void UEnemyFSM::DeadState()
{
	// ��� ���¿����� �ƹ��͵� ���� �ʴ´�.
}

void UEnemyFSM::OnDamageProcess()
{
	//// ���� Ʈ���̽��� ������ ����
	//// 1. ������
	//FVector start = me->GetActorLocation();
	//// 2. ����
	//FVector end = start + me->GetActorForwardVector() * 10000.0f;
	//// 3. ���� Ʈ���̽� �Ķ����
	//FCollisionQueryParams params;
	//params.AddIgnoredActor(me);
	//// 4. ���� Ʈ���̽� ����
	//FHitResult result;
	//GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, params);
	//// 5. ���� Ʈ���̽� ��� Ȯ��
	//if (result.bBlockingHit)
	//{
	//	// 6. ���� Ʈ���̽��� ���� ���Ͱ� ������ Ȯ��
	//	if (result.GetActor()->ActorHasTag("Enemy"))
	//	{
	//		// 7. ������ ������ �ֱ�
	//		result.GetActor()->TakeDamage(10.0f, FDamageEvent(), nullptr, me);
	//	}
	//}
	me->Destroy();
}

//void UEnemyFSM::SetTargetLocation(FVector newTargetLocation)
//{
//	EnemyLocation = newTargetLocation;
//}
