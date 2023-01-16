// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/SkeletalMeshComponent.h>
#include "EnemyFSM.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	EnemyHealth = 150;
	EnemyWalkSpeed = 300;
	EnemyRunSpeed = 800;
	
	

	// enemy mesh
	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->SetupAttachment(RootComponent);

	// enemy FSM 컴포넌트 추가
	myEnemyFSM = CreateDefaultSubobject<UEnemyFSM>(TEXT("EnemyFSM"));
}


void AEnemy::OnMyTakeDamage(float Damage)
{
	EnemyHealth -= Damage;

	if (EnemyHealth <= 0.0f)
	{
		Destroy();
	}
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
