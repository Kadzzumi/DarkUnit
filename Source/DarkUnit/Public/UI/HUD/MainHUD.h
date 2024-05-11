// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/MainWidgetController.h"
#include "MainHUD.generated.h"

class UAttributeWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UMainUserWidget;

/**
 * 
 */
UCLASS()
class DARKUNIT_API AMainHUD : public AHUD
{
	GENERATED_BODY()
public:
	//Getters
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeWidgetController* GetAttributeWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);;
protected:
	
private:
// Overlay Widget
	UPROPERTY()
	TObjectPtr<UMainUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
// Attribute Menu
	UPROPERTY()
	TObjectPtr<UAttributeWidgetController> AttributeWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeWidgetController> AttributeWidgetControllerClass;	
};
