// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

struct FInputActionValue;

UCLASS()
class TPS_PROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ATPSPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> cameraComp;
	
	// 총
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GunMesh)
	TObjectPtr<class USkeletalMeshComponent> gunMeshComp;

	// 총알
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector Direction;

	virtual void BeginPlay() override;

	UFUNCTION()
	void InputLook(const FInputActionValue& Value);

	UFUNCTION()
	void InputStartMove(const FInputActionValue& Value);

	UFUNCTION()
	void InputStopMove(const FInputActionValue& Value);

	UFUNCTION()
	void InputJump(const FInputActionValue& Value);

	UFUNCTION()
	void InputFire(const FInputActionValue& Value);
};
