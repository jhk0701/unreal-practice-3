// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

struct FInputActionValue;

UENUM(BlueprintType)
enum class EGunType : uint8
{
	None	UMETA(DisplayName = "None"),
	Rifle	UMETA(DisplayName = "Rifle Type"),
	Sniper	UMETA(DisplayName = "Sniper Type"),
};


UCLASS()
class TPS_PROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Camera|Shake")
	TSubclassOf<class UCameraShakeBase> cameraShake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
	FName handSocketName = FName("hand_rSocket");

	// 일반 총
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
	TObjectPtr<class USkeletalMeshComponent> gunMeshComp;

	// 저격 총
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
	TObjectPtr<UStaticMeshComponent> snipeMeshComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
	TObjectPtr<class UPlayerMove> playerMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
	TObjectPtr<class UPlayerFire> playerFire;

public:
	ATPSPlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
