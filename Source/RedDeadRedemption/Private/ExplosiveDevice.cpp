// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveDevice.h"

// Sets default values
AExplosiveDevice::AExplosiveDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExplosiveDevice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

