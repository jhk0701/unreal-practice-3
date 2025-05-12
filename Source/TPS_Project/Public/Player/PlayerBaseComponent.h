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
	UPlayerBaseComponent()
	{
		PrimaryComponentTick.bCanEverTick = false;

		bWantsInitializeComponent = true; // initializeComponent 함수 사용을 위한 설정
	};

	// begin 보다 먼저 호출하도록하기 위해서 initializeComponent 함수 오버라이드
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent, class ATPSPlayerController* PlayerController) {};
};
