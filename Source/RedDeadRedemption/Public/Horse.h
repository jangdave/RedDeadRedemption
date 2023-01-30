// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Horse.generated.h"

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

	UFUNCTION()
	void OverlapRide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void EndRide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Horizontal(float value);

	void Vertical(float value);

	void LookUp(float value);

	void TurnRight(float value);

	void HorseRide();

	UFUNCTION()
	void ChangeMesh(bool bChange);

	FVector direction;
};
