#include "TPSProjectGameModeBase.h"
#include "TPS_Project.h"
#include "Player/TPSPlayer.h"
#include "TPSPlayerController.h"

ATPSProjectGameModeBase::ATPSProjectGameModeBase()
{
	DefaultPawnClass = ATPSPlayer::StaticClass();
	PlayerControllerClass = ATPSPlayerController::StaticClass();
}
