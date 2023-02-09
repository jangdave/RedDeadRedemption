// Copyright Epic Games, Inc. All Rights Reserved.


#include "RedDeadRedemptionGameModeBase.h"
#include "GamePlayWidget.h"
#include "TargetCrossWidget.h"
#include "DefaultCrossWidget.h"
#include "BloodWidget.h"
#include "DeadEyeSpawn.h"
#include "RedPlayer.h"
#include "Kismet/GameplayStatics.h"

ARedDeadRedemptionGameModeBase::ARedDeadRedemptionGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARedDeadRedemptionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));

	play_UI = CreateWidget<UGamePlayWidget>(GetWorld(), gamePlayWidget);

	target_UI = CreateWidget<UTargetCrossWidget>(GetWorld(), targetCrossWidget);

	default_UI = CreateWidget<UDefaultCrossWidget>(GetWorld(), defaultCrossWidget);

	blood_UI = CreateWidget<UBloodWidget>(GetWorld(), bloodWidget);

	OnGamePlayWidget();

	CrossHairOnOff();
}

void ARedDeadRedemptionGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CrossHairchange();

	OnBlood();

	play_UI->playerHP = player->HP;

	play_UI->playerRP = player->RP;

	play_UI->dCount = player->deadCount;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADeadEyeSpawn::StaticClass(), deadeyes);
}

void ARedDeadRedemptionGameModeBase::OnGamePlayWidget()
{
	if(play_UI != nullptr)
	{
		play_UI->AddToViewport();
	}	
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
		if(player->HP < 50.0f)
		{
			blood_UI->AddToViewport();
		}
		else if(player->HP > 50.0f)
		{
			blood_UI->RemoveFromParent();
		}
	}
}
