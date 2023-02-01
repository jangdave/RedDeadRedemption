// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float forVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rigVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAir;
};
