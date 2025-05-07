#include "TPS_Project.h"
#include "TPSPlayerController.h"
#include "Player/TPSPlayer.h"
#include "Projectile/Bullet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"


ATPSPlayer::ATPSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메쉬 할당
	ConstructorHelpers::FObjectFinder<USkeletalMesh> loadedBodyMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
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
	FTransform firePoint = gunMeshComp->GetSocketTransform(TEXT("FirePoint"));
	GetWorld()->SpawnActor<ABullet>(bulletFactory, firePoint);
}
