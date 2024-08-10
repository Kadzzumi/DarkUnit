// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeWidgetController.h"

#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "PlayerController/MainPlayerState.h"

void UAttributeWidgetController::BindCallbacksToDependencies()
{
	UMainAttributeSet* AS = Cast<UMainAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
	AMainPlayerState* MainPlayerState = CastChecked<AMainPlayerState>(PlayerState);
	if (MainPlayerState)
	{
		MainPlayerState->OnAttributePointChangedDelegate.AddLambda(
			[this](int32 NewPoints)
			{
				AttributePointChangedDelegateSignature.Broadcast(NewPoints);
			}
		);
	}
	
}

void UAttributeWidgetController::BroadcastInitialValues()
{
	UMainAttributeSet* AS = Cast<UMainAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	AMainPlayerState* MainPlayerState = CastChecked<AMainPlayerState>(PlayerState);
	if (MainPlayerState)
	{
		AttributePointChangedDelegateSignature.Broadcast(MainPlayerState->GetAttributePoint());
	}
}

void UAttributeWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                        const FGameplayAttribute& Attribute) const
{
	FDarkUnitAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
	UE_LOG(LogTemp, Warning, TEXT("Broadcasting attribute with tag: %s"), *Info.AttributeTag.ToString());
}

// Adding  to  the attribute when level up
void UAttributeWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UMainAbilitySystemComponent* MainASC = CastChecked<UMainAbilitySystemComponent>(AbilitySystemComponent);
	MainASC->UpgradeAttribute(AttributeTag);
}