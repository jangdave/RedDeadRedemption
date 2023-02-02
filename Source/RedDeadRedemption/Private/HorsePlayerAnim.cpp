// Fill out your copyright notice in the Description page of Project Settings.


#include "HorsePlayerAnim.h"
#include "Horse.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHorsePlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AHorse* owner = Cast<AHorse>(TryGetPawnOwner());
	
	if (owner == nullptr)
	{
		return;
	}

	FVector velocity = owner->GetVelocity();
	FVector forwVelocity = owner->GetActorForwardVector();
	forVelocity = FVector::DotProduct(velocity, forwVelocity);
	rigVelocity = owner->h;
	bAir = owner->GetCharacterMovement()->IsFalling();

	state = owner->weaponArm;
}
