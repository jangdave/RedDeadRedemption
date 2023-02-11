// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "RedDeadRedemption/RedDeadRedemptionGameModeBase.h"

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
	isCrouching = owner->GetCharacterMovement()->IsCrouching();
}

void UPlayerAnim::OnAnim(FName sectionName)
{
	owner->PlayAnimMontage(playerMontageFactory, 1, sectionName);
}

void UPlayerAnim::OnShootAnim(FName sectionName)
{
	owner->PlayAnimMontage(playerShootMontageFactory, 1, sectionName);
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
	owner->UnRideAnimEnd();
}

void UPlayerAnim::EndDead()
{

}

void UPlayerAnim::EndReload()
{
	auto gm = Cast<ARedDeadRedemptionGameModeBase>(GetWorld()->GetAuthGameMode());
	if(owner->armWeapon == EWeaponState::RIFLE)
	{
		int32 rSetbul = gm->maxRifleAmmo - gm->rifleAmmo;

		if(gm->holdRifleAmmo < rSetbul)
		{
			gm->rifleAmmo += gm->holdRifleAmmo;
			gm->holdRifleAmmo -= gm->holdRifleAmmo;
		}
		else
		{
			gm->rifleAmmo += rSetbul;
			gm->holdRifleAmmo -= rSetbul;
		}
	}
	else if (owner->armWeapon == EWeaponState::PISTOL)
	{
		int32 pSetbul = gm->maxPistolAmmo - gm->pistolAmmo;

		if(gm->holdPistolAmmo < pSetbul)
		{
			gm->pistolAmmo += gm->holdPistolAmmo;
			gm->holdPistolAmmo -= gm->holdPistolAmmo;
		}
		else
		{
			gm->pistolAmmo += pSetbul;
			gm->holdPistolAmmo -= pSetbul;
		}
	}
}

