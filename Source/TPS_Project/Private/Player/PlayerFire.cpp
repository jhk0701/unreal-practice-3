#include "Player/PlayerFire.h"
#include "Player/PlayerAnim.h"
#include "Enemy/EnemyFSM.h"
#include "TPSPlayerController.h"
#include "Projectile/Bullet.h"
#include <Camera/CameraComponent.h>
#include <EnhancedInputComponent.h>
#include <Sound/SoundBase.h>
#include <Kismet/GameplayStatics.h>

UPlayerFire::UPlayerFire()
{
	ConstructorHelpers::FObjectFinder<USoundBase> loadedSound(TEXT("SoundWave'/Game/99-Assets/SniperGun/Rifle.Rifle'"));
	if (loadedSound.Succeeded())
	{
		bulletSound = loadedSound.Object;
	}
}

void UPlayerFire::BeginPlay()
{
	Super::BeginPlay();

	tpsController = Cast<ATPSPlayerController>(me->GetController());
	tpsController->ShowCrosshairUI();

	SetGunType(EGunType::Rifle);
}

void UPlayerFire::SetupInputBinding(UInputComponent* PlayerInputComponent, ATPSPlayerController* PlayerController)
{
	Super::SetupInputBinding(PlayerInputComponent, PlayerController);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComp->BindAction(PlayerController->FireAction, ETriggerEvent::Triggered, this, &UPlayerFire::InputFire);

	EnhancedInputComp->BindAction(PlayerController->QuickSlotAction, ETriggerEvent::Triggered, this, &UPlayerFire::InputQuickSlot);

	EnhancedInputComp->BindAction(PlayerController->AimAction, ETriggerEvent::Started, this, &UPlayerFire::InputStartAim);
	EnhancedInputComp->BindAction(PlayerController->AimAction, ETriggerEvent::Canceled, this, &UPlayerFire::InputStopAim);
}

void UPlayerFire::SetGunType(EGunType InType)
{
	curGunType = InType;
	me->gunMeshComp->SetVisibility(curGunType == EGunType::Rifle);
	me->snipeMeshComp->SetVisibility(curGunType == EGunType::Sniper);
}

void UPlayerFire::InputFire(const FInputActionValue& Value)
{
	// 카메라 진동 연출
	tpsController->PlayerCameraManager->StartCameraShake(me->cameraShake);

	// 공격 애니메이션 호출
	UPlayerAnim* playerAnim = Cast<UPlayerAnim>(me->GetMesh()->GetAnimInstance());
	playerAnim->PlayAttackAnim(); // 작성해둔 공격 애니메이션 몽타주 재생

	// 총격 사운드 재생
	UGameplayStatics::SpawnSound2D(GetWorld(), bulletSound);

	if (curGunType == EGunType::Rifle)
	{
		FTransform firePoint = me->gunMeshComp->GetSocketTransform(TEXT("FirePoint"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePoint);
	}
	else
	{
		FVector start = me->cameraComp->GetComponentLocation();
		FVector end = start + me->cameraComp->GetForwardVector() * 5000;
		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(me);

		UWorld* world = GetWorld();

		bool bHit = world->LineTraceSingleByChannel(hitInfo, start, end, ECC_Visibility, params);
		if (bHit)
		{
			FTransform hitPoint;
			hitPoint.SetLocation(hitInfo.ImpactPoint);	// 충돌 지점
			hitPoint.SetRotation(hitInfo.ImpactNormal.ToOrientationQuat()); // 충돌면

			// 총알 효과
			UGameplayStatics::SpawnEmitterAtLocation(world, bulletEffectFactory, hitPoint);

			UPrimitiveComponent* hitComp = hitInfo.GetComponent(); // 충돌한 컴포넌트
			if (hitComp && hitComp->IsSimulatingPhysics())
			{
				FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;
				hitComp->AddForce(force);
			}

			if (UEnemyFSM* enemyFsm = Cast<UEnemyFSM>(hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("EnemyFSM"))))
			{
				enemyFsm->OnDamageProcess();
			}
		}
	}
}

void UPlayerFire::InputQuickSlot(const FInputActionValue& Value)
{
	float input = Value.Get<float>();
	SetGunType((EGunType)input);
}

void UPlayerFire::InputStartAim(const FInputActionValue& Value)
{
	if (curGunType != EGunType::Sniper)
		return;

	bIsAiming = true;

	tpsController->ShowSniperUI();
	tpsController->HideCrosshairUI();

	me->cameraComp->SetFieldOfView(45.0f);
}

void UPlayerFire::InputStopAim(const FInputActionValue& Value)
{
	bIsAiming = false;

	tpsController->HideSniperUI();
	tpsController->ShowCrosshairUI();

	me->cameraComp->SetFieldOfView(90.0f);
}
