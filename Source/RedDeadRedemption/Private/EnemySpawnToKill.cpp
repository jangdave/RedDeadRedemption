// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnToKill.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "Engine/World.h"
#include "RedPlayer.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemySpawnToKill::AEnemySpawnToKill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawnToKill::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), EnemyArray);
	NumEnemy = EnemyArray.Num();
}

// Called every frame
void AEnemySpawnToKill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isSpawn == true)
	{
		currentTime += DeltaTime;

		if (currentTime > spawnTime)
		{
			SpawnEnemy();
			currentTime = 0;
		}
	}
}

void AEnemySpawnToKill::StoreEnemies()
{
	// GetAllActorsOfClass 함수를 이용해서 Enemy클래스의 모든 인스턴스를 찾는다
	TArray<AActor*> FoundActors;
	//EnemyArray에 저장하고 NumEnemy 변수설정
	EnemyArray = FoundActors;
}

void AEnemySpawnToKill::SpawnEnemy()
{
	if (enemyCount < maxCount)
	{
		// 스폰 애너미
		AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetActorLocation(), FRotator::ZeroRotator);
		enemyCount++;
	}
	else
	{
		// 스폰 멈춤
		isSpawn = false;
	}
}


