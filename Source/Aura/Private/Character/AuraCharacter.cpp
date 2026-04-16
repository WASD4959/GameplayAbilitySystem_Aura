// Copyright putuitou


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/Hud/AuraHud.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info on server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability actor info on client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* auraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(auraPlayerState);
	
	auraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(auraPlayerState, this);
	AbilitySystemComponent = auraPlayerState->GetAbilitySystemComponent();
	AttributeSet = auraPlayerState->GetAttributeSet();
	
	if (AAuraPlayerController* AuraPlayerController = GetController<AAuraPlayerController>())
	{
		if (AAuraHud* AuraHud = AuraPlayerController->GetHUD<AAuraHud>())
		{
			AuraHud->InitOverlay(AuraPlayerController, auraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
