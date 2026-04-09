// Copyright putuitou

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class IEnemyInterface;
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
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	TScriptInterface<IEnemyInterface> LastHitActor;
	TScriptInterface<IEnemyInterface> CurrentHitActor;
	
	void Move(const FInputActionValue& inputActionValue);
	void CurseTrace();
	
protected:
	virtual void BeginPlay() override;
	
	virtual	void SetupInputComponent() override;
	
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
};
