// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/SkeletalMeshComponent.h>

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
// 적 체력 다닳았을때
// void AEnemy::TakeDamage(float Damage)
// {
// 	EnemyHealth -= Damage;
// 	// 적 피가 0보다 적거나 같으면
// 	if (EnemyHealth <= 0.0f)
// 	{
// 		// 사망
// 		Destroy();
// 	}
// }