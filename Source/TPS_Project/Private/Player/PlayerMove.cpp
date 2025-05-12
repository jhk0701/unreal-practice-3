#include "Player/PlayerMove.h"
#include "TPSPlayerController.h"
#include <EnhancedInputComponent.h>


UPlayerMove::UPlayerMove()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	moveComp->MaxWalkSpeed = walkSpeed;
}

void UPlayerMove::TickComponent(float InDeltaTime, ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction)
{
	Super::TickComponent(InDeltaTime, InTickType, InThisTickFunction);

	me->AddMovementInput(Direction);
}

void UPlayerMove::SetupInputBinding(UInputComponent* PlayerInputComponent, ATPSPlayerController* PlayerController)
{
	Super::SetupInputBinding(PlayerInputComponent, PlayerController);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComp->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &UPlayerMove::InputLook);

	EnhancedInputComp->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &UPlayerMove::InputStartMove);
	EnhancedInputComp->BindAction(PlayerController->MoveAction, ETriggerEvent::Completed, this, &UPlayerMove::InputStopMove);

	EnhancedInputComp->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &UPlayerMove::InputJump);

	EnhancedInputComp->BindAction(PlayerController->RunAction, ETriggerEvent::Triggered, this, &UPlayerMove::InputStartRun);
	EnhancedInputComp->BindAction(PlayerController->RunAction, ETriggerEvent::Completed, this, &UPlayerMove::InputStopRun);
}


void UPlayerMove::InputLook(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FVector>();

	me->AddControllerPitchInput(Input.Y);
	me->AddControllerYawInput(Input.X);
}


void UPlayerMove::InputStartMove(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FVector>();
	Direction = me->GetActorForwardVector() * Input.X + me->GetActorRightVector() * Input.Y;
}

void UPlayerMove::InputStopMove(const FInputActionValue& Value)
{
	Direction = FVector::ZeroVector;
}

void UPlayerMove::InputJump(const FInputActionValue& Value)
{
	me->Jump();
}

void UPlayerMove::InputStartRun(const FInputActionValue& Value)
{
	moveComp->MaxWalkSpeed = runSpeed;
}

void UPlayerMove::InputStopRun(const FInputActionValue& Value)
{
	moveComp->MaxWalkSpeed = walkSpeed;
}
