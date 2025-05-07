// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TPS_PROJECT_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<class UProjectileMovementComponent> movementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	TObjectPtr<class USphereComponent> collisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyMesh)
	TObjectPtr<class UStaticMeshComponent> bodyMeshComp;

	float initialLifeSpan;

protected:
	virtual void BeginPlay() override;

	void Die();
};
