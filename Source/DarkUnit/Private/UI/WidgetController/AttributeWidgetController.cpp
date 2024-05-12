// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeWidgetController.h"

#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "DarkUnitGameplayTags.h"

void UAttributeWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeWidgetController::BroadcastInitialValues()
{
	UMainAttributeSet* AS = Cast<UMainAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		FDarkUnitAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value.Execute().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
		UE_LOG(LogTemp, Warning, TEXT("Broadcasting attribute with tag: %s"), *Info.AttributeTag.ToString());
	}
}
