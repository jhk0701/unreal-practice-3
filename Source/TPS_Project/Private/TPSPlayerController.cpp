// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

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
