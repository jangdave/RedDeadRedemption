// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	owner = Cast<ARedPlayer>(TryGetPawnOwner());

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

void UPlayerAnim::OnAnim(FName sectionName)
{
	owner->PlayAnimMontage(playerMontageFactory, 1, sectionName);
}

void UPlayerAnim::Throw()
{
	owner->bottleMeshComp->SetVisibility(false);
	owner->bottleFireMeshComp->SetVisibility(false);
	owner->SpawnBottle();
}

void UPlayerAnim::EndThrow()
{
	owner->bottleMeshComp->SetVisibility(true);
	owner->bottleFireMeshComp->SetVisibility(true);
	owner->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void UPlayerAnim::EndMount()
{
	owner->Ride();
}

void UPlayerAnim::EndDismount()
{

}

