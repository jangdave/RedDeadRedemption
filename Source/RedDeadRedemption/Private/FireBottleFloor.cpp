// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBottleFloor.h"

#include "Enemy.h"
#include "EnemyFSM.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFireBottleFloor::AFireBottleFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);
}

// Called when the game starts or when spawned
void AFireBottleFloor::BeginPlay()
{
	Super::BeginPlay();

	enemy = Cast<AEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy::StaticClass()));

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFireBottleFloor::OnOverlap);

	StartFloor();

	StartFire();
}

// Called every frame
void AFireBottleFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireBottleFloor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(enemy != nullptr)
	{
		enemy->myEnemyFSM->OnDamageProcess(5);
	}
}

void AFireBottleFloor::StartFloor()
{
	if(floorEffect != nullptr)
	{
		UNiagaraComponent* niagaraFloorComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), floorEffect, GetActorLocation());
	}
}

void AFireBottleFloor::StartFire()
{
	if (fireEffect != nullptr)
	{
		UNiagaraComponent* niagaraFireComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), fireEffect, GetActorLocation());
	}
}

void AFireBottleFloor::DestroySelf()
{
	Destroy();
}
