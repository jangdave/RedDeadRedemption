// Fill out your copyright notice in the Description page of Project Settings.


#include "RedPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Horse.h"
#include "WeaponWidget.h"

// Sets default values
ARedPlayer::ARedPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Cowboy/Model/Cowboy_1_1.Cowboy_1_1'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -72.0f), FRotator(0, -90.0f, 0));
	}

	springComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springComp"));
	springComp->SetupAttachment(RootComponent);
	springComp->SetRelativeLocation(FVector(0, 40.0f, 100.0f));
	springComp->TargetArmLength = 250.0f;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springComp);


	bUseControllerRotationYaw = false;
	springComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunMeshComp"));
	gunMeshComp->SetRelativeScale3D(FVector(0.5f));
	gunMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/VintageRifle/Model/VintageRifleskeletal.VintageRifleskeletal_VintageRifle'"));
	if (tempGunMesh.Succeeded())
	{
		gunMeshComp->SetSkeletalMesh(tempGunMesh.Object);

		gunMeshComp->SetRelativeLocationAndRotation(FVector(-13.0f, 47.0f, 109.0f), FRotator(0, 180.0f, -90.0f));
	}

	revolMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("revolMeshComp"));
	revolMeshComp->SetRelativeScale3D(FVector(0.15f));
	revolMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRevolMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/pistol/WWGPistol_ss.WWGPistol_ss'"));
	if (tempRevolMesh.Succeeded())
	{
		revolMeshComp->SetSkeletalMesh(tempRevolMesh.Object);

		revolMeshComp->SetRelativeLocationAndRotation(FVector(-11.0, 27.0f, 110.0f), FRotator(0, -90.0f, 0));
	}
}

// Called when the game starts or when spawned
void ARedPlayer::BeginPlay()
{
	Super::BeginPlay();

	horsePlayer = Cast<AHorse>(UGameplayStatics::GetActorOfClass(GetWorld(), AHorse::StaticClass()));
	
	weapon_UI = CreateWidget<UWeaponWidget>(GetWorld(), weaponWidget);
}

// Called every frame
void ARedPlayer::Tick(float DeltaTime)
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
void ARedPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ARedPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ARedPlayer::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &ARedPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"), this, &ARedPlayer::TurnRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ARedPlayer::Jumping);
	PlayerInputComponent->BindAction(TEXT("FireBullet"), IE_Pressed, this, &ARedPlayer::FirePressed);
	PlayerInputComponent->BindAction(TEXT("FireBullet"), IE_Released, this, &ARedPlayer::FireReleased);
	PlayerInputComponent->BindAction(TEXT("HorseRide"), IE_Pressed, this, &ARedPlayer::HorseRide);
	PlayerInputComponent->BindAction(TEXT("WeaponChange"), IE_Pressed, this, &ARedPlayer::WeaponChangePress);
	PlayerInputComponent->BindAction(TEXT("WeaponChange"), IE_Released, this, &ARedPlayer::WeaponChangeRelease);
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

void ARedPlayer::Jumping()
{
	Jump();
}

void ARedPlayer::FirePressed()
{
	FTransform t = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));

	GetWorld()->SpawnActor<ABullet>(bulletFactory, t);
}

void ARedPlayer::FireReleased()
{

}

void ARedPlayer::HorseRide()
{	
	if (bPressed != false)
	{
		//플레이어 컨트롤러 넘기기
		GetWorld()->GetFirstPlayerController()->Possess(horsePlayer);
		//플레이어 메쉬 안보이게하기
		GetMesh()->SetVisibility(false);
		gunMeshComp->SetVisibility(false);
		//플레이어 콜리젼 끄기
		this->SetActorEnableCollision(false);
		//홀스 메쉬 켜기
		horsePlayer->ChangeMesh(false);
	}
}

void ARedPlayer::WeaponChangePress()
{
	if (weapon_UI != nullptr)
	{
		weapon_UI->AddToViewport();
	}

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void ARedPlayer::WeaponChangeRelease()
{
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	weapon_UI->RemoveFromParent();
}

void ARedPlayer::ChooseWeapon(bool bRifle)
{

}

void ARedPlayer::ChangeFist()
{

}

void ARedPlayer::ChangeRifle()
{

}

void ARedPlayer::ChangePistol()
{

}

