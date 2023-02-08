// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeBeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EEnemyState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAttackPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bEnemyDieEnd;

	/*UFUNCTION(BlueprintCallable)
		void OnHitEvent()*/;

		UFUNCTION()
			void AnimNotify_OnHit();

		// 적 공격 애니메이션 노티파이
		UFUNCTION()
			void AnimNotify_OnAttack();

		UPROPERTY(EditAnywhere)
		class UAnimMontage* AttackMontage;

		UFUNCTION(BlueprintCallable)
		void OnMyAttack(FName SectionName);
	
		UPROPERTY()
			class AEnemy* me;

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
			int pose;
};
