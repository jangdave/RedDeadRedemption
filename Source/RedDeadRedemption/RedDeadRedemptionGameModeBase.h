// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RedDeadRedemptionGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API ARedDeadRedemptionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARedDeadRedemptionGameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGamePlayWidget> gamePlayWidget;

	UPROPERTY()
	class UGamePlayWidget* play_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTargetCrossWidget> targetCrossWidget;

	UPROPERTY()
	class UTargetCrossWidget* target_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDefaultCrossWidget> defaultCrossWidget;

	UPROPERTY()
	class UDefaultCrossWidget* default_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBloodWidget> bloodWidget;

	UPROPERTY()
	class UBloodWidget* blood_UI;

	UPROPERTY()
	class ARedPlayer* player;

	UPROPERTY()
	TArray<AActor*> deadeyes;

	void OnGamePlayWidget();

	void CrossHairOnOff();

	void CrossHairchange();

	void OnBlood();
};