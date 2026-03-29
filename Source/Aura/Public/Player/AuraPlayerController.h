// Copyright putuitou

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> aura_context;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> move_action;
	
	void Move(const FInputActionValue& input_action_value);
	
protected:
	virtual void BeginPlay() override;
	
	virtual	void SetupInputComponent() override;
	
public:
	AAuraPlayerController();
};
