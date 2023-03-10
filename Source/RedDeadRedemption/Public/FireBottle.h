// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBottle.generated.h"

UCLASS()
class REDDEADREDEMPTION_API AFireBottle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBottle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* bottleComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* fireComp;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* movementComp;

	UPROPERTY(EditAnywhere)
	class AFireBottleFloor* floor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFireBottleFloor> effectFloor;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* explosionImpactFactory;

	void Explode();
};
