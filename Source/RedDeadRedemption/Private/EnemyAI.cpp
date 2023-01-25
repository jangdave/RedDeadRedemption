// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "Enemy.h"

void AEnemyAI::AEnemyAIController()
{
}

// tick 함수
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveToLocation(EnemyLocation, -1.0f, false, true, false, true, 0, true);
}

// 난수 생성기
void AEnemyAI::SetNewRandomTargetLocation()
{
	// 난수 생성
	FVector RandomLocation = FMath::VRand();
	// 난수 범위 설정
	RandomLocation.X = RandomLocation.X * 1000.0f;
	RandomLocation.Y = RandomLocation.Y * 1000.0f;
	RandomLocation.Z = 0.0f;
	// 난수 위치 설정
	EnemyLocation = GetPawn()->GetActorLocation() + RandomLocation;
}

// 왼쪽 또는 오른쪽으로 움직임
void AEnemyAI::MoveToRightOrLeft()
{
	float RandomX = FMath::RandRange(-1000.0f, 1000.0f);
	
	EnemyLocation.X += RandomX;
}