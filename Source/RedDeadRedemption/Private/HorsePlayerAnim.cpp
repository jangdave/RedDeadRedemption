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
	FVector rigwVelocity = owner->GetActorRightVector();
	forVelocity = FVector::DotProduct(velocity, forwVelocity);
	rigVelocity = FVector::DotProduct(velocity, rigwVelocity);
	bAir = owner->GetCharacterMovement()->IsFalling();
}
