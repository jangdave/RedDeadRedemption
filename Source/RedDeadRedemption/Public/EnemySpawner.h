// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class REDDEADREDEMPTION_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// enemy class and a TimerHandle for the spawn timer.
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemy> EnemyClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
		float SpawnDelay;

private:
	// A timer handle for the spawn timer.
	int EnemyCount;
	FTimerHandle SpawnTimer;

	// A function to spawn an enemy.
//	void SpawnEnemy(UEnemyFSM* Enemy);
//	void OnEnemyDeath(UEnemyFSM* Enemy);
	
};
