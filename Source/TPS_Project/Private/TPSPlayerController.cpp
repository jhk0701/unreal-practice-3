// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSPlayerController.h"
#include "EnhancedInputSubsystems.h"


void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!InputMap) 
		return;

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		SubSystem->AddMappingContext(InputMap, 0);
}
