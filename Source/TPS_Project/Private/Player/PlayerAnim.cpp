#include "Player/PlayerAnim.h"
#include "Player/TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>


void UPlayerAnim::NativeUpdateAnimation(float DeltaSec)
{
	Super::NativeUpdateAnimation(DeltaSec);
	
	if (ATPSPlayer* player = Cast<ATPSPlayer>(TryGetPawnOwner()))
	{
		FVector velocity = player->GetVelocity(); // 이동 속도 벡터
		FVector forwardVector = player->GetActorForwardVector(); // 전방 벡터

		speed = FVector::DotProduct(velocity, forwardVector); // 내적으로 앞뒤 일치 여부 계산

		// 좌우 속도 계산
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(velocity, rightVector);

		// 공중에 있는지 검사
		bIsInAir = player->GetCharacterMovement()->IsFalling();
	}
}

void UPlayerAnim::PlayAttackAnim()
{
	// 공격 애니메이션 몽타주 재생
	Montage_Play(attackAnimMontage);
}
