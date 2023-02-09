// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <vector>
#include "EnemyFSM.generated.h"

// 사용할 상태 정의
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Dead
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDDEADREDEMPTION_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 상태 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		EEnemyState mState = EEnemyState::Idle;

	// 대기 상태
	void IdleState();
	// 이동 상태
	void MoveState();
	// 공격 상태
	void AttackState();
	// 피격 상태
	void DamageState();
	// 사망 상태
	void DeadState();

	// 대기 시간
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FSM")
		float IdleDelayTime = 2.0f;
	// 경과 시간
	float currentTime = 0.0f;
	bool bAttackPlay = false;
	// 타깃
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSM")
	class APawn* target;

	// 소유 액터
	UPROPERTY()
		class AEnemy* me;

	// 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSM")
		float AttackRange = 400.0f;

	// 공격 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSM")
		float AttackDelayTime = 1.5f;

	// 적 걷는 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSM")
		float EnemyWalkSpeed = 400.0f;

	// 적 뛰는 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSM")
		float EnemyRunSpeed = 600.0f;

	// 적 라이플 불릿 공장
	UPROPERTY(EditAnywhere, Category = "FSM")
		TSubclassOf<class AEnemyBullet> EnemyRifleBulletFactory;

	// 적 피스톨 불릿 공장에
	UPROPERTY(EditAnywhere, Category = "FSM")
		TSubclassOf<class AEnemyBullet> EnemyPistolBulletFactory;
	

	// 피격 알림 이벤트 함수
	void OnDamageProcess(int32 damage);
	
	// 공격 이벤트
	void OnAttackEvent();

	// AI 컨트롤러
	UPROPERTY()
		class AAIController* AI;

public:
	// 체력을 표현 하고싶다.
	int32 EnemyHealth;
	int32 EnemyMaxHealth = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCanPlayerShoot = false;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	//	FVector EnemyLocation;

	//UFUNCTION(BlueprintCallable, Category = "AI")
	//	void SetTargetLocation(FVector newTargetLocation);
	
};
