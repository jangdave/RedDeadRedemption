// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBottle.h"

#include "Components/BoxComponent.h"

// Sets default values
AFireBottle::AFireBottle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bottleComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bottleComp"));
	bottleComp->SetupAttachment(boxComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Asset/prop/Bottle.Bottle'"));
	if(tempMesh.Succeeded())
	{
		bottleComp->SetStaticMesh(tempMesh.Object);
	}

	fireComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("fireComp"));
	fireComp->SetupAttachment(bottleComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempFireMesh(TEXT("/Script/Engine.StaticMesh'/Game/Asset/prop/bomb_fire.bomb_fire'"));
	if(tempFireMesh.Succeeded())
	{
		fireComp->SetStaticMesh(tempFireMesh.Object);

		fireComp->SetRelativeLocation(FVector(0, 0, 43.0f));
	}

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
}

// Called when the game starts or when spawned
void AFireBottle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireBottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

