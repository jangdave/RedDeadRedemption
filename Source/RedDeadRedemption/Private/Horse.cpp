// Fill out your copyright notice in the Description page of Project Settings.


#include "Horse.h"
#include "Components/BoxComponent.h"
#include "RedPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "..\Public\Horse.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include <Components/SkeletalMeshComponent.h>

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

	springComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springComp"));
	springComp->SetupAttachment(RootComponent);
	springComp->SetRelativeLocationAndRotation(FVector(0, 0, 100.0f), FRotator(-30.0f, 0, 0));
	springComp->TargetArmLength = 500.0f;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springComp);

	bUseControllerRotationYaw = false;
	springComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	attachComp = CreateDefaultSubobject<USceneComponent>(TEXT("attachComp"));
	attachComp->SetupAttachment(RootComponent);
	detachComp = CreateDefaultSubobject<USceneComponent>(TEXT("detachComp"));
	detachComp->SetupAttachment(RootComponent);
	detachComp->SetRelativeLocation(FVector(0, -150.0f, -90.0f));
	playerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("playerMesh"));
	playerMesh->SetupAttachment(attachComp);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempPlayerMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Cowboy/Model/Cowboy_1_1.Cowboy_1_1'"));
	if (tempPlayerMesh.Succeeded())
	{
		playerMesh->SetSkeletalMesh(tempPlayerMesh.Object);

		playerMesh->SetRelativeLocationAndRotation(FVector(5.0f, 0, 42.0f), FRotator(0, -90.0f, 0));
	}
}

// Called when the game starts or when spawned
void AHorse::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AHorse::OverlapRide);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &AHorse::EndRide);
	boxComp->SetGenerateOverlapEvents(true);

	playerMesh->SetVisibility(false);

	player = Cast<ARedPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedPlayer::StaticClass()));
}

// Called every frame
void AHorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform trans(GetControlRotation());
	FVector resultDirection = trans.TransformVector(direction);
	resultDirection.Z = 0;
	resultDirection.Normalize();
	AddMovementInput(resultDirection);
	//방향 초기화
	direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void AHorse::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AHorse::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AHorse::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &AHorse::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"), this, &AHorse::TurnRight);
	PlayerInputComponent->BindAction(TEXT("HorseRide"), IE_Pressed, this, &AHorse::HorseRide);
}

void AHorse::OverlapRide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (player != nullptr)
	{
		player->bPressed = true;
	}
	else
	{
		return;
	}
}

void AHorse::EndRide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (player != nullptr)
	{
		player->bPressed = false;
	}
}

void AHorse::Horizontal(float value)
{
	direction.Y = value;
}

void AHorse::Vertical(float value)
{
	direction.X = value;
}

void AHorse::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AHorse::TurnRight(float value)
{
	AddControllerYawInput(value);
}

void AHorse::HorseRide()
{
	player->SetActorTransform(detachComp->GetComponentTransform());

	UGameplayStatics::GetPlayerController(this, 0)->Possess(player);

	playerMesh->SetVisibility(false);

	//플레이어 보이게 하기
	player->GetMesh()->SetVisibility(true);
	player->gunMeshComp->SetVisibility(true);
	//플레이어 콜리젼 켜기
	player->SetActorEnableCollision(true);
}

void AHorse::ChangeMesh(bool bChange)
{
	if (bChange != true)
	{
		playerMesh->SetVisibility(true);
	}
	else
	{
		return;
	}
}

