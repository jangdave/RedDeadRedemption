// Fill out your copyright notice in the Description page of Project Settings.


#include "Horse.h"
#include "Components/BoxComponent.h"
#include "RedPlayer.h"

// Sets default values
AHorse::AHorse()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/AfricanAnimalsPack/Zebra/Meshes/SK_Zebra.SK_Zebra'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeScale3D(FVector(1.2f));

		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90.0f), FRotator(0, -90.0f, 0));
	}

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	boxComp->SetupAttachment(RootComponent);
	boxComp->SetBoxExtent(FVector(100.0f, 110.0f, 32.0f));
}

// Called when the game starts or when spawned
void AHorse::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AHorse::OverlapRide);
	boxComp->SetGenerateOverlapEvents(true);
}

// Called every frame
void AHorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHorse::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHorse::OverlapRide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ARedPlayer* player= Cast<ARedPlayer>(OtherActor)
}

