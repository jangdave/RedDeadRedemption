// Copyright Epic Games, Inc. All Rights Reserved.


#include "RedDeadRedemptionGameModeBase.h"
#include "GamePlayWidget.h"
#include "TargetCrossWidget.h"
#include "DefaultCrossWidget.h"
#include "PistolBulletWidget.h"
#include "RifleBulletWidget.h"
#include "BloodWidget.h"
#include "DeadEyeSpawn.h"
#include "Horse.h"
#include "RedPlayer.h"
#include "Kismet/GameplayStatics.h"

ARedDeadRedemptionGameModeBase::ARedDeadRedemptionGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARedDeadRedemptionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CastFun();

	OnGamePlayWidget();

	CrossHairOnOff();

	HP = MaxHP;

	RP = MaxRP;
}

void ARedDeadRedemptionGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CrossHairchange();

	OnBlood();

	HPRPCharge();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADeadEyeSpawn::StaticClass(), deadeyes);
}

void ARedDeadRedemptionGameModeBase::CastFun()
{
	horse = Cast<AHorse>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));

	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));

	play_UI = CreateWidget<UGamePlayWidget>(GetWorld(), gamePlayWidget);

	target_UI = CreateWidget<UTargetCrossWidget>(GetWorld(), targetCrossWidget);

	default_UI = CreateWidget<UDefaultCrossWidget>(GetWorld(), defaultCrossWidget);

	blood_UI = CreateWidget<UBloodWidget>(GetWorld(), bloodWidget);

	pBullet_UI = CreateWidget<UPistolBulletWidget>(GetWorld(), pistolBulletWidget);

	rBullet_UI = CreateWidget<URifleBulletWidget>(GetWorld(), rifleBulletWidget);
}

void ARedDeadRedemptionGameModeBase::OnGamePlayWidget()
{
	if(play_UI != nullptr)
	{
		play_UI->AddToViewport();
	}	
}

void ARedDeadRedemptionGameModeBase::PlayerBulletSet()
{
	if(pBullet_UI != nullptr && player->armWeapon == EWeaponState::PISTOL)
	{
		pBullet_UI->AddToViewport();
	}
	else if(rBullet_UI != nullptr && player->armWeapon == EWeaponState::RIFLE)
	{
		rBullet_UI->AddToViewport();
	}
}

void ARedDeadRedemptionGameModeBase::PlayerBulletOff()
{
	if (pBullet_UI != nullptr && player->armWeapon == EWeaponState::PISTOL)
	{
		pBullet_UI->RemoveFromParent();
	}
	else if (rBullet_UI != nullptr && player->armWeapon == EWeaponState::RIFLE)
	{
		rBullet_UI->RemoveFromParent();
	}
}

void ARedDeadRedemptionGameModeBase::HorseBulletSet()
{

}

void ARedDeadRedemptionGameModeBase::HorseBulletOff()
{

}

void ARedDeadRedemptionGameModeBase::CrossHairOnOff()
{
	if(default_UI != nullptr)
	{
		default_UI->AddToViewport();
	}
}

void ARedDeadRedemptionGameModeBase::CrossHairchange()
{
	if(default_UI != nullptr && target_UI != nullptr)
	{
		if(player->bTarget != false)
		{
			default_UI->RemoveFromParent();

			target_UI->AddToViewport();
		}
		else
		{
			default_UI->AddToViewport();

			target_UI->RemoveFromParent();
		}
	}
}

void ARedDeadRedemptionGameModeBase::OnBlood()
{
	if(blood_UI != nullptr)
	{
		if(HP < 50.0f)
		{
			blood_UI->AddToViewport();
		}
		else if(HP > 50.0f)
		{
			blood_UI->RemoveFromParent();
		}
	}
}

void ARedDeadRedemptionGameModeBase::HPRPCharge()
{
	if (HP <= 100)
	{
		HP += 0.05;
	}
	if (RP <= 100)
	{
		RP += 0.05;
	}

	play_UI->playerHP = HP;

	play_UI->playerRP = RP;

	play_UI->dCount = deadCount;

	play_UI->bottleAmmo = holdBottleAmmo;

	pBullet_UI->pisAmmo = pistolAmmo;

	pBullet_UI->pisHoldAmmo = holdPistolAmmo;

	rBullet_UI->rifAmmo = rifleAmmo;

	rBullet_UI->rifHoldAmmo = holdRifleAmmo;
}
