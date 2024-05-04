// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MainAbilitySystemComponent.h"

void UMainAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMainAbilitySystemComponent::EffectApply);
}

void UMainAbilitySystemComponent::EffectApply(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffecAssetTags.Broadcast(TagContainer);
	
}
