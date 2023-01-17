// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWidget.h"
#include "RedPlayer.h"
#include "Components/Button.h"

void UWeaponWidget::NativeConstruct()
{
	btn_Rifle->OnClicked.AddDynamic(player, &ARedPlayer::ChangeRifle);
	btn_Pistal->OnClicked.AddDynamic(player, &ARedPlayer::ChangePistol);
	btn_Fist->OnClicked.AddDynamic(player, &ARedPlayer::ChangeFist);
}
