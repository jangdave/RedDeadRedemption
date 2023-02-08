// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "RedPlayer.h"
#include "Kismet/GameplayStatics.h"


void AEnemyBullet::SetDamage(float ADamage)
{
	// EnemyBullet이 닿은게 RedPlayer라면
	if (GetWorld()->GetFirstPlayerController()->GetPawn()->ActorHasTag("RedPlayer"))
	{
		// RedPlayer의 OnHit 함수 실행
		UGameplayStatics::ApplyDamage(GetWorld()->GetFirstPlayerController()->GetPawn(), ADamage, nullptr, this, nullptr);
		// RedPlayer 타입으로 캐스팅
		ARedPlayer* RedPlayer = Cast<ARedPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
		// RedPlayer의 체력을 EnemyBullet의 데미지만큼 감소
		RedPlayer->HP -= ADamage;
	}
	Destroy();
}
