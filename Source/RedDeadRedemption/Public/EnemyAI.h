// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void  AEnemyAIController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAI")
		FVector EnemyLocation;
	
	//난수 생성기
	void SetNewRandomTargetLocation();

	void MoveToRightOrLeft();
	
};
