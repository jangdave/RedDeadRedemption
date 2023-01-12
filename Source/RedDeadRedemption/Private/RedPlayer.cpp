// Fill out your copyright notice in the Description page of Project Settings.


#include "RedPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARedPlayer::ARedPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90.0f), FRotator(0, -90.0f, 0));
	}
	springComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springComp"));
	springComp->SetupAttachment(RootComponent);
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springComp);

	springComp->SetRelativeLocation(FVector(0, 40.0f, 100.0f));
	springComp->TargetArmLength = 250.0f;

	bUseControllerRotationYaw = true;
	springComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ARedPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARedPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARedPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ARedPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ARedPlayer::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &ARedPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"), this, &ARedPlayer::TurnRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ARedPlayer::Jump);
}

void ARedPlayer::Horizontal(float value)
{
	direction.Y = value;
}

void ARedPlayer::Vertical(float value)
{
	direction.X = value;
}

void ARedPlayer::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void ARedPlayer::TurnRight(float value)
{
	AddControllerYawInput(value);
}

void ARedPlayer::Jump()
{
	Jump();
}

