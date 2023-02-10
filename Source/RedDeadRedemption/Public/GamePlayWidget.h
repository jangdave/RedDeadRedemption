// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float playerHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float playerMaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float playerRP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float playerMaxRP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 dCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 bottleAmmo;
};
