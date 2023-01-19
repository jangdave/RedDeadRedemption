// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWidget.h"
#include "RedPlayer.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UWeaponWidget::NativeConstruct()
{
	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), redPlayer));

	//btn_Rifle->OnClicked.AddDynamic(player, &ARedPlayer::ChangeRifle);
	//btn_Pistol->OnClicked.AddDynamic(player, &ARedPlayer::ChangePistol);
	//btn_Fist->OnClicked.AddDynamic(player, &ARedPlayer::ChangeFist);
}
		