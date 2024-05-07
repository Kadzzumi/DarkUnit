// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MainAbilitySystemComponent.h"

#include "DarkUnitGameplayTags.h"

void UMainAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMainAbilitySystemComponent::EffectApply);

	const FDarkUnitGameplayTags& GameplayTags = FDarkUnitGameplayTags::Get();
	//GameplayTags.Attributes_Secondary_Armor.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UMainAbilitySystemComponent::EffectApply(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffecAssetTags.Broadcast(TagContainer);
	
}
