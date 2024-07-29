// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "PlayerController/MainPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMainAttributeSet* MainAttributeSet = Cast<UMainAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(MainAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MainAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(MainAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(MainAttributeSet->GetMaxStamina());
	OnManaChanged.Broadcast(MainAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MainAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AMainPlayerState* MainPlayerState = CastChecked<AMainPlayerState>(PlayerState);
	MainPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChange);
	MainPlayerState->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel)
		{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
		}
	);

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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MainAttributeSet->GetMaxManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
	if (UMainAbilitySystemComponent* MainAbilitySystemComponent = Cast<UMainAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (MainAbilitySystemComponent->bStartUpAbilitiesGiven)
		{
			OnInitializeStartUpAbilities(MainAbilitySystemComponent);
		}
		else
		{
			//
			MainAbilitySystemComponent->AbilityGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartUpAbilities);
		}
		
		// Affect the HUD from the Data Tabgle and add widgets and tags
		MainAbilitySystemComponent->EffectAssetTags.AddLambda(
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
}

void UOverlayWidgetController::OnInitializeStartUpAbilities(UMainAbilitySystemComponent* MainASC)
{
	// TODO:: GetInfo about all abilities and look up for abilities and broadcast
	if (!MainASC->bStartUpAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, MainASC](const FGameplayAbilitySpec& AbilitySpec)
	{
		FDarkUnitAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(MainASC->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = MainASC->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	MainASC->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChange(int32 NewXP) const
{
	const AMainPlayerState* MainPlayerState = CastChecked<AMainPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = MainPlayerState->LevelUpInfo;
	check(LevelUpInfo);

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level-1].LevelUpRequirement;
		
		const int32 DeltaLevelReq = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		OnCurrentXPChangedDelegate.Broadcast(XPForThisLevel);
		OnMaxXPChangedDelegate.Broadcast(DeltaLevelReq);
	}
}