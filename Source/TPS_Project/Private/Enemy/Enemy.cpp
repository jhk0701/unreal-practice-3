#include "Enemy/Enemy.h"
#include "Enemy/EnemyFSM.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
	
	USkeletalMeshComponent* mesh = GetMesh();
	ConstructorHelpers::FObjectFinder<USkeletalMesh> loadedBodyMesh(TEXT("SkeletalMesh'/Game/99-Assets/Enemy/Model/vampire_a_lusth.vampire_a_lusth'"));
	if (loadedBodyMesh.Succeeded())
	{
		mesh->SetSkeletalMesh(loadedBodyMesh.Object);
		mesh->SetRelativeLocationAndRotation(FVector(0,0,-88), FRotator(0,-90,0));
		mesh->SetRelativeScale3D(FVector(0.84f));
	}

	ConstructorHelpers::FClassFinder<UAnimInstance> loadedAnimInst(TEXT("AnimBlueprint'/Game/2-Blueprints/Enemy/ABP_Enemy.ABP_Enemy_C'"));
	if(loadedAnimInst.Succeeded())
	{
		mesh->SetAnimInstanceClass(loadedAnimInst.Class);
	}

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("EnemyFSM"));

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 돌리기
	
	UCapsuleComponent* collider = GetCapsuleComponent();
	collider->SetCollisionProfileName(UCollisionProfile::CustomCollisionProfileName);
	collider->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

