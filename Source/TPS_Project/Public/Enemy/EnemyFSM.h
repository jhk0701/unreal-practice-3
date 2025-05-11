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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	float attackRange = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	float attackDelayTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	int32 hp = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	float damageDelayTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	float dieSpeed = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	TObjectPtr<class UEnemyAnim> anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	TObjectPtr<class AAIController> ai;

	FVector randomPos;

public:	
	UEnemyFSM();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	void OnDamageProcess();

	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

protected:
	virtual void BeginPlay() override;
			
};
