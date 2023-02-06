// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBottleFloor.generated.h"

UCLASS()
class REDDEADREDEMPTION_API AFireBottleFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBottleFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* floorEffect;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* fireEffect;

	UPROPERTY(EditAnywhere)
	class USphereComponent* sphereComp;

	UPROPERTY()
	class AEnemy* enemy;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void StartFloor();

	void StartFire();

	void DestroySelf();
};
