// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TPSProjectGameModeBase.h"

void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!InputMap) 
		return;

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		SubSystem->AddMappingContext(InputMap, 0);

}

TObjectPtr<UUserWidget> ATPSPlayerController::GetSniperUI()
{
	if (!SniperUI)
		SniperUI = CreateWidget(this, SniperUIFactory);

	return SniperUI;
}

void ATPSPlayerController::ShowSniperUI()
{
	GetSniperUI()->AddToViewport();
}

void ATPSPlayerController::HideSniperUI()
{
	GetSniperUI()->RemoveFromParent();
}

TObjectPtr<UUserWidget> ATPSPlayerController::GetCrosshairUI()
{
	if (!CrosshairUI)
		CrosshairUI = CreateWidget(this, CrosshairUIFactory);

	return CrosshairUI;
}

void ATPSPlayerController::ShowCrosshairUI()
{
	GetCrosshairUI()->AddToViewport();
}

void ATPSPlayerController::HideCrosshairUI()
{
	GetCrosshairUI()->RemoveFromParent();
}

TObjectPtr<UUserWidget> ATPSPlayerController::GetGameOverUI()
{
	if (!GameOverUI)
	{
		GameOverUI = CreateWidget(this, GameOverUIFactory);
		UButton* btn = Cast<UButton>(GameOverUI->GetWidgetFromName(TEXT("BtnExit")));

		btn->OnClicked.AddDynamic(Cast<ATPSProjectGameModeBase>(GetWorld()->GetAuthGameMode()), &ATPSProjectGameModeBase::QuitGame);
	}

	return GameOverUI;
}

void ATPSPlayerController::ShowGameOverUI()
{
	GetGameOverUI()->AddToViewport();
}

void ATPSPlayerController::HideGameOverUI()
{
	GetGameOverUI()->RemoveFromParent();
}
