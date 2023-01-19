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

	UPROPERTY(EditDefaultsOnly)
	class UButton* btn_Rifle;

	UPROPERTY(EditDefaultsOnly)
	class UButton* btn_Fist;

	UPROPERTY(EditDefaultsOnly)
	class UButton* btn_Pistal;

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	class ARedPlayer* player;
	
};
