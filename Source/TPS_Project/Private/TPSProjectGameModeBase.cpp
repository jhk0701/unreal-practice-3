#include "TPSProjectGameModeBase.h"
#include "TPS_Project.h"
#include "Player/TPSPlayer.h"
#include "TPSPlayerController.h"
#include <Kismet/KismetSystemLibrary.h>

ATPSProjectGameModeBase::ATPSProjectGameModeBase()
{
	DefaultPawnClass = ATPSPlayer::StaticClass();
	PlayerControllerClass = ATPSPlayerController::StaticClass();
}

void ATPSProjectGameModeBase::QuitGame()
{
	UWorld* world = GetWorld();
	UKismetSystemLibrary::QuitGame(world, world->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
