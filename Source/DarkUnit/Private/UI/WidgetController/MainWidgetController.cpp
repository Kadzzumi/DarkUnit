// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MainWidgetController.h"

void UMainWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UMainWidgetController::BroadcastInitialValues()
{
	// Nothing
}

void UMainWidgetController::BindCallbacksToDependencies()
{
	// Do nothing
}
