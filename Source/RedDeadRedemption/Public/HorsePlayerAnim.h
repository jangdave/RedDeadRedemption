// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Horse.h"
#include "HorsePlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UHorsePlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponArm state;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float forVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rigVelocity;

	UPROPERTY()
	class AHorse* owner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float horseYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float horsePitch;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* riderMontageFactory;

	UFUNCTION(BlueprintCallable)
	void OnRiderAnim();

	UFUNCTION(BlueprintCallable)
	void EndThrow();

	UFUNCTION(BlueprintCallable)
	void Throw();
};
