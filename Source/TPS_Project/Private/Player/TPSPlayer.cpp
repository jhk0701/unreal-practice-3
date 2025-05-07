#include "Player/TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATPSPlayer::ATPSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메쉬 할당
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if(TempMesh.Succeeded())
	{
		USkeletalMeshComponent* MeshComp = GetMesh();
		MeshComp->SetSkeletalMesh(TempMesh.Object);
		
		// 위치, 방향 조절
		MeshComp->SetRelativeLocationAndRotation(FVector(0,0,-90), FRotator(0,-90,0));
	}

	// 3인칭 카메라
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraHolder"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->SetRelativeLocation(FVector(0,70,90));
	SpringArmComp->TargetArmLength = 400.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, SpringArmComp->SocketName);

	// 회전 관련 세팅
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp->bUsePawnControlRotation = false;
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

}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

