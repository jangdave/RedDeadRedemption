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
	// �� �޽�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemySettings")
		class USkeletalMeshComponent* EnemyMesh;

	// �� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySettings")
		float EnemyHealth;
	// �� �ȴ¼ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySettings")
		float EnemyWalkSpeed;
	// �� �ٴ¼ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySettings")
		float EnemyRunSpeed;
	// Track when enemies spot you
	
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
};