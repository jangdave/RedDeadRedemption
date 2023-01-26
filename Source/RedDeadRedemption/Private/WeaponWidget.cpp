// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWidget.h"
#include "RedPlayer.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UWeaponWidget::NativeConstruct()
{
	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));

	if(player != nullptr)
	{
		btn_Rifle->OnClicked.AddDynamic(player, &ARedPlayer::ChangeRifle);
		btn_Pistol->OnClicked.AddDynamic(player, &ARedPlayer::ChangePistol);
		btn_Fist->OnClicked.AddDynamic(player, &ARedPlayer::ChangeFist);
	}
}

/*void UWeaponWidget::Rifle()
{
	player->ChooseWeapon(EWeaponState::RIFLE);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	GetWorld()->GetFirstPlayerController()->AController::SetIgnoreLookInput(false);
	//GetWorld()->GetFirstPlayerController();
	this->RemoveFromParent();
}

void UWeaponWidget::Pistol()
{
	player->ChooseWeapon(EWeaponState::PISTOL);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	GetWorld()->GetFirstPlayerController()->AController::SetIgnoreLookInput(false);
	//GetWorld()->GetFirstPlayerController();
	this->RemoveFromParent();
}

void UWeaponWidget::Fist()
{
	player->ChooseWeapon(EWeaponState::FIST);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	GetWorld()->GetFirstPlayerController()->AController::SetIgnoreLookInput(false);
	//GetWorld()->GetFirstPlayerController();
	this->RemoveFromParent();
}*/
		