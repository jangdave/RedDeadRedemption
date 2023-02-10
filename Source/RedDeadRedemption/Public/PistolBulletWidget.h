// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PistolBulletWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UPistolBulletWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 pisAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 pisHoldAmmo;
};
