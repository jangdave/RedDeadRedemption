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

	bool isPistol;

	bool isRifle;

	bool isFist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float forwordVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rightVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isInAir;

	FORCEINLINE void SetWeapon(EWeaponState weaponState) { if(weaponState == EWeaponState::FIST)
	{
		isPistol = true;
		isRifle = false;
	} }
};
