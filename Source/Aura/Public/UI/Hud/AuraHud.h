// Copyright putuitou

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHud.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHud : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams WidgetControllerParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
protected:
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
};
