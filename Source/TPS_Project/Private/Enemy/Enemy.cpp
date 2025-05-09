#include "Enemy/Enemy.h"
#include "Enemy/EnemyFSM.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> loadedBodyMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
	if (loadedBodyMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(loadedBodyMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-88), FRotator(0,-90,0));
	}

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("EnemyFSM"));

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 돌리기
	
	UCapsuleComponent* collider = GetCapsuleComponent();
	collider->SetCollisionProfileName(UCollisionProfile::CustomCollisionProfileName);
	collider->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
