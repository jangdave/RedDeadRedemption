// Fill out your copyright notice in the Description page of Project Settings.


#include "RedPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Bullet.h"
#include "FireBottle.h"
#include "Kismet/GameplayStatics.h"
#include "Horse.h"
#include "PlayerAnim.h"
#include "PlayerPistolBullet.h"
#include "PlayerRifleBullet.h"
#include "WeaponWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/Controller.h"

// Sets default values
ARedPlayer::ARedPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/PolygonWestern/Meshes/Characters/SK_Character_Cowboy_01.SK_Character_Cowboy_01'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90.0f), FRotator(0, -90.0f, 0));
	}
	
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunMeshComp"));
	gunMeshComp->SetRelativeScale3D(FVector(1));
	gunMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/PolygonWestern/Meshes/Weapons/SK_Wep_Rifle_01.SK_Wep_Rifle_01'"));
	if (tempGunMesh.Succeeded())
	{
		gunMeshComp->SetSkeletalMesh(tempGunMesh.Object);

		gunMeshComp->SetRelativeLocationAndRotation(FVector(-21.0f, 47.0f, 136.0f), FRotator(0, 0, 0));
	}

	revolMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("revolMeshComp"));
	revolMeshComp->SetRelativeScale3D(FVector(1));
	revolMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRevolMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/PolygonWestern/Meshes/Weapons/SK_Wep_Revolver_01.SK_Wep_Revolver_01'"));
	if (tempRevolMesh.Succeeded())
	{
		revolMeshComp->SetSkeletalMesh(tempRevolMesh.Object);

		revolMeshComp->SetRelativeLocationAndRotation(FVector(-17.0, 50.0f, 134.0f), FRotator(0, 0, 0));
	}

	bottleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bottleMeshComp"));
	bottleMeshComp->SetupAttachment(GetMesh());
	bottleFireMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bottleFireMeshComp"));
	bottleFireMeshComp->SetupAttachment(bottleMeshComp);

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
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	ConstructorHelpers::FClassFinder<UAnimInstance> tempAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/player/ABP_RedPlayer.ABP_RedPlayer_C'"));
	if(tempAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnim.Class);
	}
}

// Called when the game starts or when spawned
void ARedPlayer::BeginPlay()
{
	Super::BeginPlay();

	horsePlayer = Cast<AHorse>(UGameplayStatics::GetActorOfClass(GetWorld(), AHorse::StaticClass()));
	
	weapon_UI = CreateWidget<UWeaponWidget>(GetWorld(), weaponWidget);

	fireBottle = Cast<AFireBottle>(UGameplayStatics::GetActorOfClass(GetWorld(), fireBottleFactory));

	playerAnim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());

	ChooseWeapon(EWeaponState::FIST);
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
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ARedPlayer::RunPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &ARedPlayer::RunReleased);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ARedPlayer::CrouchPressed);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &ARedPlayer::CrouchReleased);
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
	switch (armWeapon)
	{
	case EWeaponState::FIST:
		FireFist();
		break;

	case EWeaponState::PISTOL:
		FirePistol();
		break;

	case EWeaponState::RIFLE:
		FireRifle();
		break;

	case EWeaponState::FIREBOTTLE:
		FireBottle();
		break;

	default:
		break;
	}
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
		revolMeshComp->SetVisibility(false);
		//플레이어 콜리젼 끄기
		this->SetActorEnableCollision(false);
		//홀스 메쉬 켜기
		horsePlayer->ChangeMesh(false);
		bIsRide = true;

		if (armWeapon == EWeaponState::FIREBOTTLE)
		{
			horsePlayer->ChooseWeapon(EWeaponArm::FIREBOTTLE);
		}
		else if (armWeapon == EWeaponState::FIST)
		{
			horsePlayer->ChooseWeapon(EWeaponArm::FIST);
		}
		else if (armWeapon == EWeaponState::PISTOL)
		{
			horsePlayer->ChooseWeapon(EWeaponArm::PISTOL);
		}
		else if (armWeapon == EWeaponState::RIFLE)
		{
			horsePlayer->ChooseWeapon(EWeaponArm::RIFLE);
		}

		ChooseWeapon(EWeaponState::FIST);
	}
}

void ARedPlayer::WeaponChangePress()
{
	if (weapon_UI && false == weapon_UI->IsInViewport())
	{
		weapon_UI->AddToViewport();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		GetWorld()->GetFirstPlayerController()->AController::SetIgnoreLookInput(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetWorld()->GetFirstPlayerController(), weapon_UI);
	}
	//UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void ARedPlayer::RunPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = runSpeed;
}

void ARedPlayer::RunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void ARedPlayer::CrouchPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = crouchSpeed;
}

void ARedPlayer::CrouchReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void ARedPlayer::ChangeFist()
{
	if(bIsRide != true)
	{
		if (weapon_UI != nullptr && true == weapon_UI->IsInViewport())
		{
			weapon_UI->RemoveFromParent();
			ControllerWidget();
			ChooseWeapon(EWeaponState::FIST);
		}
	}
}

void ARedPlayer::ChangeRifle()
{
	if(bIsRide != true)
	{
		if (weapon_UI != nullptr && true == weapon_UI->IsInViewport())
		{
			weapon_UI->RemoveFromParent();
			ControllerWidget();
			ChooseWeapon(EWeaponState::RIFLE);
		}
	}
}

void ARedPlayer::ChangePistol()
{
	if (weapon_UI != nullptr && true == weapon_UI->IsInViewport())
	{
		weapon_UI->RemoveFromParent();
		ControllerWidget();
		ChooseWeapon(EWeaponState::PISTOL);
	}
}

void ARedPlayer::ChangeBottle()
{
	if(weapon_UI != nullptr && true == weapon_UI->IsInViewport())
	{
		weapon_UI->RemoveFromParent();
		ControllerWidget();
		ChooseWeapon(EWeaponState::FIREBOTTLE);
	}
}

void ARedPlayer::ControllerWidget()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	GetWorld()->GetFirstPlayerController()->AController::SetIgnoreLookInput(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
}

void ARedPlayer::ChooseWeapon(EWeaponState val)
{
	switch (val)
	{
	case EWeaponState::FIST:
			gunMeshComp->SetVisibility(false);
			revolMeshComp->SetVisibility(false);
			bottleMeshComp->SetVisibility(false);
			bottleFireMeshComp->SetVisibility(false);
			armWeapon = val;
			playerAnim->state = armWeapon;
		break;

	case EWeaponState::PISTOL:
			gunMeshComp->SetVisibility(false);
			revolMeshComp->SetVisibility(true);
			bottleMeshComp->SetVisibility(false);
			bottleFireMeshComp->SetVisibility(false);
			armWeapon = val;
			playerAnim->state = armWeapon;
		break;

	case EWeaponState::RIFLE:
			gunMeshComp->SetVisibility(true);
			revolMeshComp->SetVisibility(false);
			bottleMeshComp->SetVisibility(false);
			bottleFireMeshComp->SetVisibility(false);
			armWeapon = val;
			playerAnim->state = armWeapon;
		break;

	case EWeaponState::FIREBOTTLE:
			gunMeshComp->SetVisibility(false);
			revolMeshComp->SetVisibility(false);
			bottleMeshComp->SetVisibility(true);
			bottleFireMeshComp->SetVisibility(true);
			armWeapon = val;
			playerAnim->state = armWeapon;
	default:
		break;
	}
}

void ARedPlayer::FirePistol()
{
	FTransform t = revolMeshComp->GetSocketTransform(TEXT("SK_Wep_Revolver_01_CylinderSocket"));
	//t.SetScale3D(FVector(1));
	GetWorld()->SpawnActor<APlayerPistolBullet>(pistolBulletFactory, t);
}

void ARedPlayer::FireRifle()
{
	FTransform t = gunMeshComp->GetSocketTransform(TEXT("SK_Wep_Rifle_01_SlideSocket"));
	//t.SetScale3D(FVector(1));
	GetWorld()->SpawnActor<APlayerRifleBullet>(rifleBulletFactory, t);
}

void ARedPlayer::FireFist()
{

}

void ARedPlayer::FireBottle()
{
	GetWorld()->SpawnActor<AFireBottle>(fireBottleFactory, GetActorLocation() + (GetActorUpVector() * 10.0f) + (GetActorForwardVector() * 70.0f), GetControlRotation());
}