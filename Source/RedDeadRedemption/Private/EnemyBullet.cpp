// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "RedPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.h"
#include "Components/SphereComponent.h"

void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnHit);
}

void AEnemyBullet::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 총알이 플레이어에게 맞았을 때
	if (OtherActor->IsA(ARedPlayer::StaticClass()))
	{
		// 플레이어 타입으로 캐스팅
		ARedPlayer* player = Cast<ARedPlayer>(OtherActor);
		
		// 만약 닿은게 player라면 OnDamage함수를 실행하고 데미지를 넘겨준다.
		if (player)
		{
			player->OnDamage(Damage);
			UE_LOG(LogTemp, Warning, TEXT("Hittest"));
		}
		// 총알 파괴
		Destroy();
	}
}


