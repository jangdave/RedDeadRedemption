// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWidget.h"
#include "RedPlayer.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<ARedPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (!btn_Rifle->OnClicked.IsAlreadyBound(this, &UWeaponWidget::Rifle))
	{
		btn_Rifle->OnClicked.AddDynamic(this, &UWeaponWidget::Rifle);
	}
	if (!btn_Pistol->OnClicked.IsAlreadyBound(this, &UWeaponWidget::Pistol))
	{
		btn_Pistol->OnClicked.AddDynamic(this, &UWeaponWidget::Pistol);
	}
	if (!btn_Fist->OnClicked.IsAlreadyBound(this, &UWeaponWidget::Fist))
	{
		btn_Fist->OnClicked.AddDynamic(this, &UWeaponWidget::Fist);
	}
}

void UWeaponWidget::Rifle()
{
	player->ChangeRifle();
}

void UWeaponWidget::Pistol()
{
	player->ChangePistol();
}

void UWeaponWidget::Fist()
{
	player->ChangeFist();
}
