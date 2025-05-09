#include "Player/PlayerAnim.h"
#include "Player/TPSPlayer.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSec)
{
	Super::NativeUpdateAnimation(DeltaSec);
	
	if (ATPSPlayer* player = Cast<ATPSPlayer>(TryGetPawnOwner()))
	{
		// 이동 속도 벡터
		FVector velocity = player->GetVelocity();

		// 전방 벡터
		FVector forwardVector = player->GetActorForwardVector();

		// 내적으로 앞뒤 일치 여부 계산
		speed = FVector::DotProduct(velocity, forwardVector);
	}
}
