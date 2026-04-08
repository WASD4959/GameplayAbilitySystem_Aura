// Copyright putuitou

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> abilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> attributeSet;
	
public:
	AAuraPlayerState();
		
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const {return attributeSet;};
};
