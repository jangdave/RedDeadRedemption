// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "EnemyBullet.generated.h"

/**
 * 
 */
UCLASS()
class REDDEADREDEMPTION_API AEnemyBullet : public ABullet
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
// bullet damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBullet")
	float Damage = 10.0f;

	
	// 총알 데미지 함수 overlap
	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 총알 지나갈때 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBullet")
		class USoundBase* BulletPewPewSound;
};
