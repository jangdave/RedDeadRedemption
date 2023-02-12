// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnToKill.generated.h"

UCLASS()
class REDDEADREDEMPTION_API AEnemySpawnToKill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnToKill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
// TArray<AActor> 변수 만들기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		TArray<AActor*> EnemyArray;
// 적의 수를 저장할 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		int NumEnemy;
	//적 배열에 저장하는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void StoreEnemies();

	// 에너미 생성 변수
	void SpawnEnemy();
	
	UPROPERTY()
		bool isSpawn = false;

	UPROPERTY()
		float currentTime = 0.0f;
	
	UPROPERTY()
		float spawnTime = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY()
		int enemyCount = 0;

	UPROPERTY()
		int maxCount = 5;
};
