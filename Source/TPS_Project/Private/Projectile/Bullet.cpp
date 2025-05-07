#include "Projectile/Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	collisionComp->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	collisionComp->SetSphereRadius(13);
	SetRootComponent(collisionComp);

	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (TempMesh.Succeeded())
	{
		bodyMeshComp->SetStaticMesh(TempMesh.Object);
		bodyMeshComp->SetRelativeLocation(FVector(0,0,-12.5f));
	}

	bodyMeshComp->SetRelativeScale3D(FVector(0.25f));
	bodyMeshComp->SetupAttachment(collisionComp);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movementComp->SetUpdatedComponent(collisionComp); // 움직일 컴포넌트 설정
	movementComp->InitialSpeed = 5000;
	movementComp->MaxSpeed = 5000;
	movementComp->bShouldBounce = true;
	movementComp->Bounciness = 0.3f;

	initialLifeSpan = 2.0f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, initialLifeSpan, false);
	// 람다형태 구현
	/*
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]() 
		{
			Destroy();
		}), initialLifeSpan, false);
	*/
}

void ABullet::Die()
{
	Destroy();
}
