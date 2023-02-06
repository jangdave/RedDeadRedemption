// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveDevice.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AExplosiveDevice::AExplosiveDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Radius"));
	SphereComp->SetupAttachment(RootComponent);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AExplosiveDevice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveDevice::Explosion()
{
	// 폭발 카운트가 0이 아니라면
	if (ExplosionCount > 0)
	{
		// 폭발 카운트를 1씩 감소
		ExplosionCount -= 1;
	}
	// 폭발 카운트가 0이라면
	else
	{
		// 폭발 이펙트 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, FVector(1.0f), true);

		//// 폭발 범위 내의 적들을 찾아서
		TArray<AActor*> OverlapActors;
		SphereComp->GetOverlappingActors(OverlapActors);

		// 적들의 상태를 죽음으로 변경
		for (auto OverlapActor : OverlapActors)
		{
			Enemy = Cast<AEnemy>(OverlapActor);
			if (Enemy)
			{
				Enemy->myEnemyFSM->mState = EEnemyState::Dead;
			}
		}

		// 폭발 장치 제거
		Destroy();
	}
}

