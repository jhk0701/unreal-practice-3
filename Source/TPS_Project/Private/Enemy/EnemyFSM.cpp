#include "Enemy/EnemyFSM.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyAnim.h"
#include "Player/TPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "TPS_Project.h"
#include <Components/CapsuleComponent.h>
#include <AIController.h>
#include <NavigationSystem.h>
#include <Navigation/PathFollowingComponent.h>


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

	// AAIController 할당하기
	
	if (AController* controller = owner->GetController())
	{
		ai = Cast<AAIController>(owner->GetController());
	}
	else
	{
		PRINT_LOG(TEXT("Controller is null"));
		owner->Destroy();
	}
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

		// 최초 랜덤한 위치 정하기
		GetRandomPositionInNavMesh(owner->GetActorLocation(), 500, randomPos);
	}
}

void UEnemyFSM::MoveState()
{
	FVector destination = target->GetActorLocation();
	FVector dir = destination - owner->GetActorLocation();
	// owner->AddMovementInput(dir.GetSafeNormal());
	
	// ai->MoveToLocation(destination); // 목표 지점으로 이동하라 (이전버전 : 단순 이동)

	// 내비게이션 시스템 활용
	// 먼저 길을 찾아보도록 시도
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FPathFindingQuery query;
	FAIMoveRequest req;

	// 목적지에서 인지할 수 있는 범위
	req.SetAcceptanceRadius(3);
	req.SetGoalLocation(destination);

	// 길 찾기를 위한 쿼리작성
	ai->BuildPathfindingQuery(req, query);

	// 길 찾기 결과 가져오기
	FPathFindingResult r = ns->FindPathSync(query);

	if(r.Result == ENavigationQueryResult::Success)
	{
		ai->MoveToLocation(destination);
	}
	else 
	{
		// 길을 찾지 못하면 랜덤 위치를 패트롤
		auto result = ai->MoveToLocation(randomPos);

		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			// 도착 시 새로운 랜덤 위치 구하기
			GetRandomPositionInNavMesh(owner->GetActorLocation(), 500, randomPos);
		}
	}

	// dir.Size() < attackRange; // 벡터의 길이로 계산하기
	if (dir.SizeSquared() < attackRange * attackRange) // 계산 최적화
	{
		mState = EEnemyState::Attack;
		ai->StopMovement();
	}
}

void UEnemyFSM::AttackState()
{
	elapsedTime += GetWorld()->DeltaTimeSeconds;

	if (elapsedTime > attackDelayTime) 
	{
		elapsedTime = 0;

		// 공격
		// PRINT_LOG(TEXT("Enemy Attack"));
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
	ai->StopMovement();

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


bool UEnemyFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);

	dest = loc.Location;

	return result;;
}
