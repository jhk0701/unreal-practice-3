#include "Enemy/EnemyFSM.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyAnim.h"
#include "Player/TPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "TPS_Project.h"
#include <Components/CapsuleComponent.h>


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

	anim = Cast<UEnemyAnim>(owner->GetMesh()->GetAnimInstance());
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

	anim->animState = mState;
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

	// dir.Size() < attackRange; // 벡터의 길이로 계산하기
	if (dir.SizeSquared() < attackRange * attackRange) // 계산 최적화
	{
		mState = EEnemyState::Attack;
	}
}

void UEnemyFSM::AttackState()
{
	elapsedTime += GetWorld()->DeltaTimeSeconds;

	if (elapsedTime > attackDelayTime) 
	{
		elapsedTime = 0;

		// 공격
		PRINT_LOG(TEXT("Enemy Attack"));
		anim->bAttackPlay = true;
	}

	float distance = FVector::DistSquared(target->GetActorLocation(), owner->GetActorLocation());
	if (distance > attackRange * attackRange)
	{
		mState = EEnemyState::Move;
		elapsedTime = 0;
	}

}


void UEnemyFSM::DamageState()
{
	elapsedTime += GetWorld()->DeltaTimeSeconds;

	if (elapsedTime > damageDelayTime)
	{
		mState = EEnemyState::Idle;
		elapsedTime = 0;
	}
}

void UEnemyFSM::DieState()
{
	if (!anim->bDieDone)
		return;

	FVector downLocation = owner->GetActorLocation() + dieSpeed * GetWorld()->DeltaTimeSeconds * FVector::DownVector;
	owner->SetActorLocation(downLocation);

	if(downLocation.Z < - 200.f)
		owner->Destroy();
}

void UEnemyFSM::OnDamageProcess()
{
	if (hp <= 0)
		return;
	
	--hp;

	if (hp > 0)
	{
		elapsedTime = 0;
		mState = EEnemyState::Damage;

		int32 r = FMath::RandRange(0, 1);
		anim->PlayDamageAnim(FName(FString::Printf(TEXT("Damage%d"), r)));
	}
	else
	{
		owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		mState = EEnemyState::Die;
		anim->PlayDamageAnim(TEXT("Die"));
	}
}
