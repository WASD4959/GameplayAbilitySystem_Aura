// Copyright putuitou


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CurseTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(auraContext);
	
	UEnhancedInputLocalPlayerSubsystem* sub_system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(sub_system);
	sub_system->AddMappingContext(auraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& inputActionValue)
{
	const FVector2D inputAxisValue = inputActionValue.Get<FVector2D>();
	const FRotator controllerRotation = GetControlRotation();
	const FRotator yawRotation = FRotator(0, controllerRotation.Yaw, 0);
	
	const FVector forward = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector right = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forward, inputAxisValue.Y);
		controlledPawn->AddMovementInput(right, inputAxisValue.X);
	}
}

void AAuraPlayerController::CurseTrace()
{
	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit == false) return;
	
	currentHitActor = hitResult.GetActor();
	if (lastHitActor == currentHitActor)
	{
		return;
	}
	
	if (lastHitActor != nullptr)
	{
		lastHitActor->UnHeightLightActor();
	}
	
	if (currentHitActor != nullptr)
	{
		currentHitActor->HeightLightActor();
	}
	
	lastHitActor = currentHitActor;
}

