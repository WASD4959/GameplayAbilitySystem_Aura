// Copyright putuitou


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(aura_context);
	
	UEnhancedInputLocalPlayerSubsystem* sub_system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(sub_system);
	sub_system->AddMappingContext(aura_context, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI input_mode_data;
	input_mode_data.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	input_mode_data.SetHideCursorDuringCapture(false);
	SetInputMode(input_mode_data);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* enhanced_input_component = CastChecked<UEnhancedInputComponent>(InputComponent);
	enhanced_input_component->BindAction(move_action, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& input_action_value)
{
	const FVector2D input_axis_value = input_action_value.Get<FVector2D>();
	const FRotator controller_rotation = GetControlRotation();
	const FRotator yaw_rotation = FRotator(0, controller_rotation.Yaw, 0);
	
	const FVector forward = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
	const FVector right = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* controlled_pawn = GetPawn<APawn>())
	{
		controlled_pawn->AddMovementInput(forward, input_axis_value.Y);
		controlled_pawn->AddMovementInput(right, input_axis_value.X);
	}
}

