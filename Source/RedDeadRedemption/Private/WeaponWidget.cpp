// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWidget.h"

#include "Horse.h"
#include "RedPlayer.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<ARedPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	horse = Cast<AHorse>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

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
	if (!btn_Bottle->OnClicked.IsAlreadyBound(this, &UWeaponWidget::Bottle))
	{
		btn_Bottle->OnClicked.AddDynamic(this, &UWeaponWidget::Bottle);
	}
}

void UWeaponWidget::Rifle()
{
	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(),ARedPlayer::StaticClass()));
	if(player->bIsRide != true)
	{
		player->ChangeRifle();
	}
	else
	{
		horse->ChangeRifle();
		
	}
}

void UWeaponWidget::Pistol()
{
	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));
	if (player->bIsRide != true)
	{
		player->ChangePistol();
	}
	else
	{
		horse->ChangePistol();
	}
}

void UWeaponWidget::Fist()
{
	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));
	if (player->bIsRide != true)
	{
		player->ChangeFist();
	}
	else
	{
		horse->ChangeFist();
	}
}

void UWeaponWidget::Bottle()
{
	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));
	if (player->bIsRide != true)
	{
		player->ChangeBottle();
	}
	else
	{
		horse->ChangeBottle();
	}
}
