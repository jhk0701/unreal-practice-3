// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBaseComponent.h"
#include "PlayerFire.generated.h"

/**
 * 
 */
UCLASS()
class TPS_PROJECT_API UPlayerFire : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	TObjectPtr<class ATPSPlayerController> tpsController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Type")
	EGunType curGunType{ EGunType::None };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Aim")
	bool bIsAiming;

	// 총알
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun|Bullet|BulletFactory")
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun|Bullet|Effect")
	TObjectPtr<class UParticleSystem> bulletEffectFactory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun|Bullet|Effect")
	TObjectPtr<class USoundBase> bulletSound;


public:
	UPlayerFire();

	virtual void BeginPlay() override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent, class ATPSPlayerController* PlayerController) override;

	void SetGunType(EGunType InType);

	UFUNCTION()
	void InputFire(const FInputActionValue& Value);

	UFUNCTION()
	void InputQuickSlot(const FInputActionValue& Value);

	UFUNCTION()
	void InputStartAim(const FInputActionValue& Value);

	UFUNCTION()
	void InputStopAim(const FInputActionValue& Value);
};
