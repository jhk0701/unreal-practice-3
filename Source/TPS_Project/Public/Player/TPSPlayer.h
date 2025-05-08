// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UENUM(BlueprintType)
enum class EGunType : uint8
{
	None	UMETA(DisplayName = "None"),
	Rifle	UMETA(DisplayName = "Rifle Type"),
	Sniper	UMETA(DisplayName = "Sniper Type"),
};

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Type")
	EGunType curGunType {EGunType::None};

	// 일반 총
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Mesh")
	TObjectPtr<class USkeletalMeshComponent> gunMeshComp;

	// 저격 총
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Mesh")
	TObjectPtr<UStaticMeshComponent> snipeMeshComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Aim")
	bool bIsAiming;

	// 총알
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun|Bullet|BulletFactory")
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun|Bullet|Effect")
	TObjectPtr<class UParticleSystem> bulletEffectFactory;

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

	UFUNCTION()
	void InputQuickSlot(const FInputActionValue& Value);

	void SetGunType(EGunType InType);

	UFUNCTION()
	void InputStartAim(const FInputActionValue& Value);

	UFUNCTION()
	void InputStopAim(const FInputActionValue& Value);
};
