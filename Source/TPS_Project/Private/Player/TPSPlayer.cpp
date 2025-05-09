#include "TPS_Project.h"
#include "TPSPlayerController.h"
#include "Player/TPSPlayer.h"
#include "Projectile/Bullet.h"
#include "Enemy/EnemyFSM.h"
#include "Player/PlayerAnim.h"
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>

ATPSPlayer::ATPSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메쉬 할당
	ConstructorHelpers::FObjectFinder<USkeletalMesh> loadedBodyMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if(loadedBodyMesh.Succeeded())
	{
		USkeletalMeshComponent* MeshComp = GetMesh();
		MeshComp->SetSkeletalMesh(loadedBodyMesh.Object);
		
		// 위치, 방향 조절
		MeshComp->SetRelativeLocationAndRotation(FVector(0,0,-90), FRotator(0,-90,0));
	}

	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	gunMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> loadedGunMesh(TEXT("SkeletalMesh'/Game/99-Assets/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	if(loadedGunMesh.Succeeded())
	{
		gunMeshComp->SetSkeletalMesh(loadedGunMesh.Object);
		gunMeshComp->SetRelativeLocation(FVector(-14, 52, 120));
	}
	
	snipeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SnipeMesh"));
	snipeMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<UStaticMesh> loadedSnipeMesh(TEXT("StaticMesh'/Game/99-Assets/SniperGun/sniper11.sniper11'"));
	if(loadedSnipeMesh.Succeeded())
	{
		snipeMeshComp->SetStaticMesh(loadedSnipeMesh.Object);
		snipeMeshComp->SetRelativeLocation(FVector(-22, 55, 150));
		snipeMeshComp->SetRelativeScale3D(FVector(0.15f));
	}

	// 3인칭 카메라
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraHolder"));
	springArmComp->SetupAttachment(GetRootComponent());
	springArmComp->SetRelativeLocation(FVector(0,70,90));
	springArmComp->TargetArmLength = 400.f;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(springArmComp, springArmComp->SocketName);

	// 회전 관련 세팅
	springArmComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	
	tpsController = Cast<ATPSPlayerController>(GetController());
	tpsController->ShowCrosshairUI();

	SetGunType(EGunType::Rifle);
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(Direction);
}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ATPSPlayerController* PlayerController = Cast<ATPSPlayerController>(GetWorld()->GetFirstPlayerController());

	EnhancedInputComp->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ATPSPlayer::InputLook);
	
	EnhancedInputComp->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ATPSPlayer::InputStartMove);
	EnhancedInputComp->BindAction(PlayerController->MoveAction, ETriggerEvent::Completed, this, &ATPSPlayer::InputStopMove);
	
	EnhancedInputComp->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ATPSPlayer::InputJump);
	
	EnhancedInputComp->BindAction(PlayerController->FireAction, ETriggerEvent::Triggered, this, &ATPSPlayer::InputFire);
	
	EnhancedInputComp->BindAction(PlayerController->QuickSlotAction, ETriggerEvent::Triggered, this, &ATPSPlayer::InputQuickSlot);
	
	EnhancedInputComp->BindAction(PlayerController->AimAction, ETriggerEvent::Started, this, &ATPSPlayer::InputStartAim);
	EnhancedInputComp->BindAction(PlayerController->AimAction, ETriggerEvent::Canceled, this, &ATPSPlayer::InputStopAim);

	EnhancedInputComp->BindAction(PlayerController->RunAction, ETriggerEvent::Triggered, this, &ATPSPlayer::InputStartRun);
	EnhancedInputComp->BindAction(PlayerController->RunAction, ETriggerEvent::Completed, this, &ATPSPlayer::InputStopRun);
}

void ATPSPlayer::InputLook(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FVector>();

	AddControllerPitchInput(Input.Y);
	AddControllerYawInput(Input.X);
}


void ATPSPlayer::InputStartMove(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FVector>();
	Direction = GetActorForwardVector() * Input.X + GetActorRightVector() * Input.Y;
}

void ATPSPlayer::InputStopMove(const FInputActionValue& Value)
{
	Direction = FVector::ZeroVector;
}

void ATPSPlayer::InputJump(const FInputActionValue& Value)
{
	Jump();
}

void ATPSPlayer::InputFire(const FInputActionValue& Value)
{
	// 공격 애니메이션 호출
	UPlayerAnim* playerAnim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	playerAnim->PlayAttackAnim(); // 작성해둔 공격 애니메이션 몽타주 재생

	if(curGunType == EGunType::Rifle)
	{
		FTransform firePoint = gunMeshComp->GetSocketTransform(TEXT("FirePoint"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePoint);
	}
	else
	{
		FVector start = cameraComp->GetComponentLocation();
		FVector end = start + cameraComp->GetForwardVector() * 5000;
		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);

		UWorld* world = GetWorld();

		bool bHit = world->LineTraceSingleByChannel(hitInfo, start, end, ECC_Visibility, params);
		if(bHit)
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

			 if(UEnemyFSM* enemyFsm = Cast<UEnemyFSM>(hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("EnemyFSM"))))
			 {
				 enemyFsm->OnDamageProcess();
			 }
		}
	}
}

void ATPSPlayer::InputQuickSlot(const FInputActionValue& Value)
{
	float input = Value.Get<float>();
	SetGunType((EGunType)input);
}

void ATPSPlayer::SetGunType(EGunType InType)
{
	curGunType = InType;
	gunMeshComp->SetVisibility(curGunType == EGunType::Rifle);
	snipeMeshComp->SetVisibility(curGunType == EGunType::Sniper);
}


void ATPSPlayer::InputStartAim(const FInputActionValue& Value)
{
	if (curGunType != EGunType::Sniper)
		return;

	bIsAiming = true;

	tpsController->ShowSniperUI();
	tpsController->HideCrosshairUI();

	cameraComp->SetFieldOfView(45.0f);
}

void ATPSPlayer::InputStopAim(const FInputActionValue& Value)
{
	bIsAiming = false;

	tpsController->HideSniperUI();
	tpsController->ShowCrosshairUI();

	cameraComp->SetFieldOfView(90.0f);
}

void ATPSPlayer::InputStartRun(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = runSpeed;
}

void ATPSPlayer::InputStopRun(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

