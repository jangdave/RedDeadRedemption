// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY()
	class ARedDeadRedemptionGameModeBase* gm;

	UFUNCTION(BlueprintCallable)
	void GameStart();

	UPROPERTY(EditAnywhere)
	class USoundBase* BGM;

	UAudioComponent* bgm;
};
