#include "Player/PlayerBaseComponent.h"

UPlayerBaseComponent::UPlayerBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<ATPSPlayer>(GetOwner());
	moveComp = me->GetCharacterMovement();
}
