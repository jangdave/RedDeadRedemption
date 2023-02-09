// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RedPlayer.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	FIST,
	RIFLE,
	PISTOL,
	FIREBOTTLE,
};

UCLASS()
class REDDEADREDEMPTION_API ARedPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARedPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponState armWeapon;

	UPROPERTY(EditAnywhere)
	class UPlayerAnim* playerAnim;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerPistolBullet> pistolBulletFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerRifleBullet> rifleBulletFactory;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* gunMeshComp;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* revolMeshComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* bottleMeshComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* bottleFireMeshComp;
	
	UPROPERTY(EditAnywhere)
	class AHorse* horsePlayer;

	UPROPERTY(EditAnywhere)
	class AFireBottle* fireBottle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFireBottle> fireBottleFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWeaponWidget> weaponWidget;

	UPROPERTY()
	class UWeaponWidget* weapon_UI;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* gunEnemyImpactFactory;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* pistolEnemyImpactFactory;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* GroundImpactFactory;

	UPROPERTY(EditAnywhere)
	class USoundBase* gunFireSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* pistolFireSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* groundImpactSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* enemyImpactSound;

	void Horizontal(float value);

	void Vertical(float value);

	void LookUp(float value);

	void TurnRight(float value);

	void Jumping();

	void FirePressed();

	void FireReleased();

	void HorseRide();

	UFUNCTION()
	void HorseUnRide();

	UFUNCTION()
	void UnRideAnimEnd();

	void WeaponChangePress();

	void RunPressed();

	void RunTime();

	void RunReleased();

	void TargetOnPressed();

	void TargetOnReleased();

	void CrouchPressed();

	void CrouchReleased();

	UFUNCTION()
	void ChangeFist();

	UFUNCTION()
	void ChangeRifle();

	UFUNCTION()
	void ChangePistol();

	UFUNCTION()
	void ChangeBottle();

	UFUNCTION()
	void ControllerWidget();

	void ChooseWeapon(EWeaponState val);

	FVector direction;

	bool bPossessed = true;

	UPROPERTY(EditDefaultsOnly)
	bool bPressed;
	
	void FirePistol();

	void FireRifle();

	void FireFist();

	void FireBottle();

	void OnDeadEye();

	void OffDeadEye();

	UFUNCTION()
	void SpawnBottle();

	float walkSpeed = 400.0f;

	float runSpeed = 600.0f;

	float crouchSpeed = 200.0f;

	bool bIsRide;

	bool bTarget;
	
	UPROPERTY(EditAnywhere)
	float HP;

	UPROPERTY(EditAnywhere)
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere)
	float RP;

	UPROPERTY(EditAnywhere)
	float MaxRP = 100.0f;

	void HPRPCharge();

	void SpawnEmitter(UParticleSystem* factory, FTransform transform);

	void PlaySound(USoundBase* sound, FVector location);

	UFUNCTION()
	void OnDamage(float damage);
	
	//UPROPERTY(EditAnywhere)
	//bool bFire;

	UFUNCTION()
	void Ride();

	bool bDeadEye;

	void DeadEyeTarget();

	UPROPERTY()
	TArray<AActor*> enemies;

	void DestroyEnemy();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADeadEyeSpawn> deadFactory;

	UPROPERTY()
	class ARedDeadRedemptionGameModeBase* gm;

	UPROPERTY(EditAnywhere)
	int32 deadCount = 3;
};