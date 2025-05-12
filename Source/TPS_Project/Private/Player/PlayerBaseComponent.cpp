#include "Player/PlayerBaseComponent.h"

void UPlayerBaseComponent::InitializeComponent()
{
	me = Cast<ATPSPlayer>(GetOwner());
	moveComp = me->GetCharacterMovement();

	me->OnInputBinding.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);
}

void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

}
