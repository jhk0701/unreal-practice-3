#include "TPS_Project.h"
#include "TPSPlayerController.h"
#include "Player/TPSPlayer.h"
#include "Player/PlayerAnim.h"
#include "Player/PlayerMove.h"
#include "Player/PlayerFire.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <EnhancedInputComponent.h>

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
	gunMeshComp->SetupAttachment(GetMesh(), handSocketName); // 손 소켓에 붙이기
	gunMeshComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> loadedGunMesh(TEXT("SkeletalMesh'/Game/99-Assets/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	if (loadedGunMesh.Succeeded())
	{
		gunMeshComp->SetSkeletalMesh(loadedGunMesh.Object);
		gunMeshComp->SetRelativeLocationAndRotation(FVector(-17, 10, -3), FRotator(0, 90, 0));
	}

	snipeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SnipeMesh"));
	snipeMeshComp->SetupAttachment(GetMesh(), handSocketName);
	snipeMeshComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	ConstructorHelpers::FObjectFinder<UStaticMesh> loadedSnipeMesh(TEXT("StaticMesh'/Game/99-Assets/SniperGun/sniper11.sniper11'"));
	if (loadedSnipeMesh.Succeeded())
	{
		snipeMeshComp->SetStaticMesh(loadedSnipeMesh.Object);
		FTransform localTransform = FTransform(FRotator(0, 90, 0).Quaternion(), FVector(-42, 7, 1), FVector(0.15f));

		snipeMeshComp->SetRelativeTransform(localTransform);
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

	
	// 이동 컴포넌트 생성
	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));

	// 공격 컴포넌트 생성
	playerFire = CreateDefaultSubobject<UPlayerFire>(TEXT("PlayerFire"));
}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	ATPSPlayerController* PlayerController = Cast<ATPSPlayerController>(GetWorld()->GetFirstPlayerController());

	OnInputBinding.Broadcast(PlayerInputComponent, PlayerController);
	// playerMove->SetupInputBinding(PlayerInputComponent, PlayerController);
	// playerFire->SetupInputBinding(PlayerInputComponent, PlayerController);
}
