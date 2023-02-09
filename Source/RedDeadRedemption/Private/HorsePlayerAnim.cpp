// Fill out your copyright notice in the Description page of Project Settings.


#include "HorsePlayerAnim.h"
#include "Horse.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHorsePlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	owner = Cast<AHorse>(TryGetPawnOwner());
	
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

void UHorsePlayerAnim::OnRiderAnim()
{
	owner->playerMesh->GetAnimInstance()->Montage_Play(riderMontageFactory);
}

void UHorsePlayerAnim::EndThrow()
{
	owner->bottleMeshComp->SetVisibility(true);
	owner->bottleFireMeshComp->SetVisibility(true);
}

void UHorsePlayerAnim::Throw()
{
	owner->SpawnHorseBottle();
	owner->bottleMeshComp->SetVisibility(false);
	owner->bottleFireMeshComp->SetVisibility(false);
}
