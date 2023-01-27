// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "MinimapCamera.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API AMinimapCamera : public ASceneCapture2D
{
	GENERATED_BODY()

public:
	AMinimapCamera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//class ARedPlayer* player;
};
