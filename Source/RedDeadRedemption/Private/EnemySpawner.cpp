// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	// 스폰 타이머를 시작
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, SpawnDelay, true);

	Player = Cast<ARedPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckPlayerDistance();
}

void AEnemySpawner::CheckPlayerDistance()
{
	// 플레이어와의 거리를 계산
	FVector PlayerLocation = Player->GetActorLocation();

	// 플레이어와 스포너 사이의 거리
	float Distance = FVector::Dist(PlayerLocation, GetActorLocation());

	// 만약 플레이어가 스포너의 반경 안에 들어오는 순간
	if (Distance <= PlayerDetectionRange)
	{
		// 스폰 타이머를 한번만 시작
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, SpawnDelay, true);
		UE_LOG(LogTemp, Warning, TEXT("Player Detected"));

	}
	else // 나가는 순간
	{
		// 스폰 타이머를 멈춤
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}

}

void AEnemySpawner::SpawnEnemy()
{
	// 스폰 애너미
	AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetActorLocation(), FRotator::ZeroRotator);
	// 애너미 스폰 카운트 증가
	EnemiesSpawned += 1;

	// 설정한 최대 애너미 수를 넘어서면
	if (EnemiesSpawned >= MaxEnemySpawn)
	{
		// 스폰 타이머를 멈춤
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}

}

