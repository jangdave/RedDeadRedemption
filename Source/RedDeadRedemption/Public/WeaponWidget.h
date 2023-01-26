// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_Rifle;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_Fist;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_Pistol;

	virtual void NativeConstruct() override;

	UPROPERTY()
	class ARedPlayer* player;

	/*UFUNCTION()
	void Rifle();

	UFUNCTION()
	void Pistol();

	UFUNCTION()
	void Fist();*/
};
