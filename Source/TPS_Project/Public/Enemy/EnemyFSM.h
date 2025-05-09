#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_PROJECT_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 2;
	float elapsedTime = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	TObjectPtr<class ATPSPlayer> target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	TObjectPtr<class AEnemy> owner;

	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRAnge = 150.0f;

public:	
	UEnemyFSM();

	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
			
};
