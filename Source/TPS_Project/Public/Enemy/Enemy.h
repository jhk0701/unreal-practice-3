#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TPS_PROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	TObjectPtr<class UEnemyFSM> fsm;


public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
