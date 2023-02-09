// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadEyeSpawn.h"
#include "Components/BoxComponent.h"

// Sets default values
ADeadEyeSpawn::ADeadEyeSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
}

// Called when the game starts or when spawned
void ADeadEyeSpawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADeadEyeSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

