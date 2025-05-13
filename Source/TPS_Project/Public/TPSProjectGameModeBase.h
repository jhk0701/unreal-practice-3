#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPS_PROJECT_API ATPSProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPSProjectGameModeBase();

	void GameOver();

	UFUNCTION()
	void QuitGame();

};
