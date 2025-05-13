// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = false;

	// /Script/Engine.Blueprint'/Game/2-Blueprints/Enemy/BP_TPSEnemy.BP_TPSEnemy_C'
	ConstructorHelpers::FClassFinder<AEnemy> tempEnemy(TEXT("Blueprint'/Game/2-Blueprints/Enemy/BP_TPSEnemy.BP_TPSEnemy_C'"));
	if(tempEnemy.Succeeded())
	{
		enemyFactory = tempEnemy.Class;
	}
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	float timeDelay = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(
		spawnTimer,
		this,
		&AEnemyManager::CreateEnemy,
		timeDelay,
		false
	);
}


void AEnemyManager::CreateEnemy()
{
	if (spawnPoints.Num() < 1)
		return;

	int32 idx = FMath::RandRange(0, spawnPoints.Num() - 1);
	GetWorld()->SpawnActor<AActor>(enemyFactory, spawnPoints[idx]->GetTransform());

	float timeDelay = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(
		spawnTimer,
		this,
		&AEnemyManager::CreateEnemy,
		timeDelay,
		false
	);
}

