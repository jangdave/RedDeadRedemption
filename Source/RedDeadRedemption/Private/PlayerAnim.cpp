// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ARedPlayer* owner = Cast<ARedPlayer>(TryGetPawnOwner());

	if(owner == nullptr)
	{
		return;
	}
	FVector velocity = owner->GetVelocity();
	FVector forVelocity = owner->GetActorForwardVector();
	FVector rigVelocity = owner->GetActorRightVector();
	forwordVelocity = FVector::DotProduct(velocity, forVelocity);
	rightVelocity = FVector::DotProduct(velocity, rigVelocity);
	isInAir = owner->GetCharacterMovement()->IsFalling();
}
