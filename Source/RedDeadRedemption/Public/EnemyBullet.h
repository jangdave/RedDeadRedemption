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

public:
// bullet damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBullet")
	float Damage = 10.0f;

	// fuction to set damage
	UFUNCTION(BlueprintCallable, Category = "EnemyBullet")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
