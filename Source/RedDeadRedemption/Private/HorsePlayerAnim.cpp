// Fill out your copyright notice in the Description page of Project Settings.


#include "HorsePlayerAnim.h"
#include "Horse.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RedDeadRedemption/RedDeadRedemptionGameModeBase.h"

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
	owner->playerMesh->GetAnimInstance()->Montage_Play(ThrowMontage);
}

void UHorsePlayerAnim::FireAnim()
{
	owner->playerMesh->GetAnimInstance()->Montage_Play(FireMontage);
}

void UHorsePlayerAnim::ReloadAnim()
{
	owner->playerMesh->GetAnimInstance()->Montage_Play(ReloadMontage);
}

void UHorsePlayerAnim::EndReload()
{
	auto gm = Cast<ARedDeadRedemptionGameModeBase>(GetWorld()->GetAuthGameMode());
	if(owner->weaponArm == EWeaponArm::RIFLE)
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
	else if(owner->weaponArm == EWeaponArm::PISTOL)
	{
		int32 pSetbul = gm->maxPistolAmmo - gm->pistolAmmo;

		if (gm->holdPistolAmmo < pSetbul)
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
