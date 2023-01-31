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
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btn_Rifle;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btn_Fist;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btn_Pistol;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btn_Bottle;
		
	UPROPERTY()
	class ARedPlayer* player;

	UPROPERTY()
	class AHorse* horse;

	UFUNCTION()
	void Rifle();

	UFUNCTION()
	void Pistol();

	UFUNCTION()
	void Fist();

	UFUNCTION()
	void Bottle();
};
