// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "RedDeadRedemption/RedDeadRedemptionGameModeBase.h"

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	gm = Cast<ARedDeadRedemptionGameModeBase>(GetWorld()->GetAuthGameMode());

	bgm = Cast<UAudioComponent>(UGameplayStatics::SpawnSound2D(GetWorld(), BGM));

	StartButton->OnClicked.AddDynamic(this, &UStartWidget::GameStart);

	GetWorld()->GetFirstPlayerController()->AController::SetIgnoreLookInput(false);
}

void UStartWidget::GameStart()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	
	gm->OnGamePlayWidget();

	gm->CrossHairOnOff();

	bgm->Stop();

	this->RemoveFromParent();
}
