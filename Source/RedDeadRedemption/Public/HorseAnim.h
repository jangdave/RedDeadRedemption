// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HorseAnim.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UHorseAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float forwordVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rightVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAir;
};
