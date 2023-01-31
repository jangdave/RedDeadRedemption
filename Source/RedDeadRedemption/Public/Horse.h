// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Horse.generated.h"

UENUM(BlueprintType)
enum class EWeaponArm : uint8
{
	FIST,
	RIFLE,
	PISTOL,
	FIREBOTTLE,
};

UCLASS()
class REDDEADREDEMPTION_API AHorse : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHorse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponArm weaponArm;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComp;
	
	UPROPERTY(EditAnywhere)
	class USceneComponent* attachComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* detachComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* playerMesh;
	
	UPROPERTY(EditAnywhere)
	class ARedPlayer* player;

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
	TSubclassOf<class AFireBottle> fireBottleFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWeaponWidget> weaponWidget;

	UPROPERTY()
	class UWeaponWidget* weapon_UI;

	void ChooseWeapon(EWeaponArm val);
	
	UFUNCTION()
	void OverlapRide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void EndRide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Horizontal(float value);

	void Vertical(float value);

	void LookUp(float value);

	void TurnRight(float value);

	void HorseRide();

	void FirePressed();

	void WeaponChangePressed();

	void ControllerWidget();

	void FirePistol();

	void FireRifle();

	void FireFist();

	void FireBottle();

	UFUNCTION()
	void ChangeFist();

	UFUNCTION()
	void ChangeRifle();

	UFUNCTION()
	void ChangePistol();

	UFUNCTION()
	void ChangeBottle();

	UFUNCTION()
	void ChangeMesh(bool bChange);

	FVector direction;
};
