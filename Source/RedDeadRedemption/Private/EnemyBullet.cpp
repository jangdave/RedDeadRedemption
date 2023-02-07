// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "RedPlayer.h"

void AEnemyBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// if the bullet hits the player
	if (OtherActor->IsA(ARedPlayer::StaticClass()))
	{
		// cast the actor to the player
		ARedPlayer* Player = Cast<ARedPlayer>(OtherActor);

		// if the player is valid
		if (Player)
		{
			// apply damage to the player
			Player->OnDamage(20);
		}
	}

	// destroy the bullet
	Destroy();
}
