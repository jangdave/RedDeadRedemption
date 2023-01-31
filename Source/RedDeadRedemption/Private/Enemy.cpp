// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/SkeletalMeshComponent.h>
#include "EnemyFSM.h"
#include "EnemyBullet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	// enemy mesh
	// constructorhelpers를 이용해서 캐릭터의 메쉬를 가져온다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempEnemyMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/PolygonWestern/Meshes/Characters/SK_Character_Badguy_01.SK_Character_Badguy_01'"));
	// 불러오는데 성공했다면
	if (TempEnemyMesh.Succeeded())
	{
		// 메쉬를 GetMesh로 적용한다.
		GetMesh()->SetSkeletalMesh(TempEnemyMesh.Object);
		// transform을 설정한다.
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
		// scale 수정
		GetMesh()->SetRelativeScale3D(FVector(1.0f));
	}

	// 라이플의 컴포넌트를 만들고 싶다.
	GunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	GunMeshComp->SetupAttachment(GetMesh());
	// 라이플의 에셋을 읽어서 컴포넌트에 적용한다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/PolygonWestern/Meshes/Weapons/SK_Wep_Rifle_01.SK_Wep_Rifle_01'"));
	// 만약 적용이 성공했다면
	if (TempGunMesh.Succeeded())
	{
		// 라이플의 메쉬를 GunMeshComp에 적용한다.
		GunMeshComp->SetSkeletalMesh(TempGunMesh.Object);
		// transform을 설정한다.
		GunMeshComp->SetRelativeLocationAndRotation(FVector(0.0f, 60.0f, 140.0f), FRotator(0.0f, 0.0f, 0.0f));
		// scale 수정
		GunMeshComp->SetRelativeScale3D(FVector(1.0f));
	}


	// enemy FSM 컴포넌트 추가
	myEnemyFSM = CreateDefaultSubobject<UEnemyFSM>(TEXT("EnemyFSM"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
}


void AEnemy::OnMyTakeDamage(float Damage)
{

	//EnemyHealth -= Damage;

	//if (EnemyHealth <= 0.0f)
	//{
	//	Destroy();
	//}
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 총알과의 Overlap을 감지하기 위한 함수
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);

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

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	// OtherActor가 PlayerPistolBullet 이라면
	if (OtherActor->IsA<ABullet>())
	{
		// EnemyFSM으로 enemy에게 데미지를 주고 싶다.
		myEnemyFSM->OnDamageProcess(10.0f);

		UE_LOG(LogTemp, Warning, TEXT("Hit"));
	}
	
}
