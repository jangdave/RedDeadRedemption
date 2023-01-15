// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class REDDEADREDEMPTION_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	// 적 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemySettings")
		class USkeletalMeshComponent* EnemyMesh;

	// 적 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySettings")
		float EnemyHealth;
	// 적 걷는속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySettings")
		float EnemyWalkSpeed;
	// 적 뛰는속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySettings")
		float EnemyRunSpeed;
	// 적 받는 피해
	UFUNCTION(BlueprintCallable, Category = "EnemySettings")
		void TakeDamage(float Damage);
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	// 적 AI 관리 컴포넌트 클래스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FMSComponent")
		class UEnemyFSM* EnemyFSM;

	
};
