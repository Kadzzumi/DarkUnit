// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMainAttributeSet* MainAttributeSet = Cast<UMainAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(MainAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MainAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(MainAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(MainAttributeSet->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMainAttributeSet* MainAttributeSet = Cast<UMainAttributeSet>(AttributeSet);
	//Update Report Changes in the data
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetStaminaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetMaxStaminaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		}
	);
	// Affect the HUD from the Data Tabgle and add widgets and tags
	Cast<UMainAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (FGameplayTag Tag : AssetTags)
			{
				
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}

