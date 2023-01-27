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
	class AHorse* horsePlayer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWeaponWidget> weaponWidget;

	UPROPERTY()
	class UWeaponWidget* weapon_UI;

	void Horizontal(float value);

	void Vertical(float value);

	void LookUp(float value);

	void TurnRight(float value);

	void Jumping();

	void FirePressed();

	void FireReleased();

	void HorseRide();

	void WeaponChangePress();
	
	UFUNCTION()
	void ChangeFist();

	UFUNCTION()
	void ChangeRifle();

	UFUNCTION()
	void ChangePistol();

	UFUNCTION()
	void ControllerWidget();

	void ChooseWeapon(EWeaponState val);

	FVector direction;

	bool bPossessed = true;

	bool bPressed = false;

	bool bChooseRifle;

	EWeaponState armWeapon;

	void FirePistol();

	void FireRifle();

	void FireFist();
};