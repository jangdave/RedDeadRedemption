// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveDevice.generated.h"

UCLASS()
class REDDEADREDEMPTION_API AExplosiveDevice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveDevice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ¹Ú½º ÄÞÇÁ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosive Settings")
		class UBoxComponent* BoxComp;

	// ½ºÇÇ¾î ÄÞÇÁ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosive Settings")
		class USphereComponent* SphereComp;

	// ¸Þ½Ã ÄÞÇÁ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosive Settings")
		class UStaticMeshComponent* MeshComp;

	// Æø¹ß Ä«¿îÆ®
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosive Settings")
		float ExplosionCount = 0;

	// Æø¹ß Æã¼Ç
	UFUNCTION(BlueprintCallable)
		void Explosion();

	// Æø¹ß È¿°ú
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosive Settings")
		class UParticleSystem* ExplosionEffect;

	class UEnemyFSM* EnemyFSM;
	
	class AEnemy* Enemy;
};
