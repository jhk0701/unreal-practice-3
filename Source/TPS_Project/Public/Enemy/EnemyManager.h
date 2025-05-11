// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class TPS_PROJECT_API AEnemyManager : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = SpawnSetting)
	TSubclassOf<class AEnemy> enemyFactory;

	UPROPERTY(EditAnywhere, Category = SpawnSetting)
	TArray<AActor*> spawnPoints;

	UPROPERTY(EditAnywhere, Category = SpawnSetting)
	float minTime = 1.f;

	UPROPERTY(EditAnywhere, Category = SpawnSetting)
	float maxTime = 3.f;

	FTimerHandle spawnTimer;

public:	
	AEnemyManager();

	void CreateEnemy();

protected:
	virtual void BeginPlay() override;


};
