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

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPistolBulletWidget> pistolBulletWidget;

	UPROPERTY()
	class UPistolBulletWidget* pBullet_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class URifleBulletWidget> rifleBulletWidget;

	UPROPERTY()
	class URifleBulletWidget* rBullet_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverWidget> gameOverWidget;

	UPROPERTY()
	class UGameOverWidget* gameover_UI;

	UPROPERTY()
	class ARedPlayer* player;

	UPROPERTY()
	class AHorse* horse;

	UPROPERTY()
	TArray<AActor*> deadeyes;

	void OnGamePlayWidget();

	void CrossHairOnOff();

	void CrossHairchange();

	void OnBlood();

	void CastFun();

	void PlayerBulletSet();

	void PlayerBulletOff();

	void HorseBulletSet();

	void HorseBulletOff();

	void HPRPCharge();
	
	void GameOver();

	UPROPERTY(EditAnywhere)
	float HP;

	UPROPERTY(EditAnywhere)
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere)
	float RP;

	UPROPERTY(EditAnywhere)
	float MaxRP = 100.0f;

	UPROPERTY(EditAnywhere)
	int32 deadCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 maxPistolAmmo = 6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 pistolAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 holdPistolAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 maxRifleAmmo = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 rifleAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 holdRifleAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 holdBottleAmmo;

};