// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RedPlayer.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponState state;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float forwordVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rightVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isTargetOn;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* playerMontageFactory;

	UPROPERTY()
	class ARedPlayer* owner;

	UFUNCTION(BlueprintCallable)
	void OnAnim(FName sectionName);

	UFUNCTION(BlueprintCallable)
	void EndThrow();

	UFUNCTION(BlueprintCallable)
	void Throw();

	UFUNCTION(BlueprintCallable)
	void EndMount();

	UFUNCTION(BlueprintCallable)
	void EndDismount();
};
