// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class TPS_PROJECT_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float walkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float runSpeed = 600.0f;

public:
	UPlayerMove();

	virtual void BeginPlay() override;
	virtual void TickComponent(float InDeltaTime, ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent, class ATPSPlayerController* PlayerController) override;

	UFUNCTION()
	void InputLook(const FInputActionValue& Value);

	UFUNCTION()
	void InputStartMove(const FInputActionValue& Value);
	UFUNCTION()
	void InputStopMove(const FInputActionValue& Value);

	UFUNCTION()
	void InputJump(const FInputActionValue& Value);

	UFUNCTION()
	void InputStartRun(const FInputActionValue& Value);
	UFUNCTION()
	void InputStopRun(const FInputActionValue& Value);
};
