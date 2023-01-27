// Copyright Epic Games, Inc. All Rights Reserved.


#include "RedDeadRedemptionGameModeBase.h"
#include "GamePlayWidget.h"
#include "Kismet/GameplayStatics.h"

ARedDeadRedemptionGameModeBase::ARedDeadRedemptionGameModeBase()
{

}

void ARedDeadRedemptionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	play_UI = CreateWidget<UGamePlayWidget>(GetWorld(), gamePlayWidget);
	
	OnGamePlayWidget();
}

void ARedDeadRedemptionGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARedDeadRedemptionGameModeBase::OnGamePlayWidget()
{
	if(play_UI != nullptr)
	{
		play_UI->AddToViewport();
	}	
}
