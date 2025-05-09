#include "Enemy/EnemyFSM.h"
#include "Enemy/Enemy.h"
#include "Player/TPSPlayer.h"
#include <Kismet/GameplayStatics.h>


UEnemyFSM::UEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSPlayer::StaticClass());
	target = Cast<ATPSPlayer>(actor);
	owner = Cast<AEnemy>(GetOwner());
}

void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;

	case EEnemyState::Move:
		MoveState();
		break;

	case EEnemyState::Attack:
		AttackState();
		break;

	case EEnemyState::Damage:
		DamageState();
		break;

	case EEnemyState::Die:
		DieState();
		break;

	default:
		IdleState();
		break;
	}
}


void UEnemyFSM::IdleState()
{
	elapsedTime += GetWorld()->DeltaTimeSeconds;

	if(elapsedTime > idleDelayTime)
	{
		mState = EEnemyState::Move;
		elapsedTime = 0;
	}
}

void UEnemyFSM::MoveState()
{
	FVector destination = target->GetActorLocation();
	FVector dir = destination - owner->GetActorLocation();
	owner->AddMovementInput(dir.GetSafeNormal());
}

void UEnemyFSM::AttackState()
{
}

void UEnemyFSM::DamageState()
{
}

void UEnemyFSM::DieState()
{
}