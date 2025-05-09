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

protected:
	TObjectPtr<class ATPSPlayerController> tpsController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> cameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Type")
	EGunType curGunType{ EGunType::None };

	// 일반 총
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Mesh")
	TObjectPtr<class USkeletalMeshComponent> gunMeshComp;

	// 저격 총
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Mesh")
	TObjectPtr<UStaticMeshComponent> snipeMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Socket")
	FName handSocketName = FName("hand_rSocket");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun|Aim")
	bool bIsAiming;

	// 총알
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun|Bullet|BulletFactory")
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun|Bullet|Effect")
	TObjectPtr<class UParticleSystem> bulletEffectFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float walkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float runSpeed = 600.0f;

public:
	ATPSPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
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

	UFUNCTION()
	void InputStartRun(const FInputActionValue& Value);
	UFUNCTION()
	void InputStopRun(const FInputActionValue& Value);

};
