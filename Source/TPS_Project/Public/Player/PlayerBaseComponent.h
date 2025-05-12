#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_PROJECT_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Common)
	TObjectPtr<ATPSPlayer> me;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Common)
	TObjectPtr<UCharacterMovementComponent> moveComp;

public:	
	UPlayerBaseComponent();
	virtual void BeginPlay() override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent, class ATPSPlayerController* PlayerController) {};
};
