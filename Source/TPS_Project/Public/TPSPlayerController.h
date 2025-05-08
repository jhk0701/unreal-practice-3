// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class TPS_PROJECT_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputMappingContext> InputMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> QuickSlotAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Sniper")
	TSubclassOf<class UUserWidget> SniperUIFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Sniper")
	TObjectPtr<UUserWidget> SniperUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Crosshair")
	TSubclassOf<UUserWidget> CrosshairUIFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Crosshair")
	TObjectPtr<UUserWidget> CrosshairUI;

	TObjectPtr<UUserWidget> GetSniperUI();
	void ShowSniperUI();
	void HideSniperUI();

	TObjectPtr<UUserWidget> GetCrosshairUI();
	void ShowCrosshairUI();
	void HideCrosshairUI();

protected:
	virtual void BeginPlay() override;
	
};
