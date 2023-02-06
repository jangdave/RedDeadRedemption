// Fill out your copyright notice in the Description page of Project Settings.


#include "HorseAnim.h"
#include "Horse.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHorseAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AHorse* owner = Cast<AHorse>(TryGetPawnOwner());

	if (owner == nullptr)
	{
		return;
	}
	FVector velocity = owner->GetVelocity();
	FVector forVelocity = owner->GetActorForwardVector();
	forwordVelocity = FVector::DotProduct(velocity, forVelocity);
	rightVelocity = owner->h;
	isAir = owner->GetCharacterMovement()->IsFalling();
}
