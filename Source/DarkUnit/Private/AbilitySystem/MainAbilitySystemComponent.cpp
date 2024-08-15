// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MainAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/Abilities/DarkUnitGameplayAbility.h"
#include "DarkUnit/DarkUnitLogChannels.h"
#include "Interaction/InteractionInterface.h"

void UMainAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMainAbilitySystemComponent::EffectApply);
}
// Add Abilities
void UMainAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UDarkUnitGameplayAbility* DarkUnitAbility = Cast<UDarkUnitGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(DarkUnitAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
	bStartUpAbilitiesGiven = true;
	AbilityGivenDelegate.Broadcast(this);
}

void UMainAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartUpPassiveAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartUpPassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}
//
//Weapon Abilities
void UMainAbilitySystemComponent::AddWeaponAbilities(const TSubclassOf<UGameplayAbility> WeaponAbilities)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(WeaponAbilities, 1);
	if (const UDarkUnitGameplayAbility* DarkUnitAbility = Cast<UDarkUnitGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.DynamicAbilityTags.AddTag(DarkUnitAbility->StartupInputTag);
		GiveAbility(AbilitySpec);
	}
	AbilityGivenDelegate.Broadcast(this); 
}

void UMainAbilitySystemComponent::RemoveWeaponAbilities(const TSubclassOf<UGameplayAbility> WeaponAbilities)
{
	// Iterate over the abilities to find the one to remove
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.Ability->GetClass() == WeaponAbilities)
		{
			// Remove the ability from the Ability System Component
			ClearAbility(AbilitySpec.Handle);
		}
	}
}


// Inputs
void UMainAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			TryActivateAbility(AbilitySpec.Handle);
			if (!AbilitySpec.IsActive())
			{
				
			}
		}
	}
}
void UMainAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	/*
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
	*/
}

void UMainAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
			
		}
	}	
}

void UMainAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogDarkUnit, Error, TEXT("Failed to execute: %hs"), __FUNCTION__);	
		}
	}
}
void UMainAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	if (!bStartUpAbilitiesGiven)
	{
		bStartUpAbilitiesGiven = true;
		AbilityGivenDelegate.Broadcast(this);
	}
}

//
FGameplayTag UMainAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Conjuration"))) || Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("EssenceBond"))) || Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Sigil"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UMainAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag Tag : AbilitySpec.DynamicAbilityTags)
	{
		if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

void UMainAbilitySystemComponent::EffectApply(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTags.Broadcast(TagContainer);
	
}

// Upgrading attribute when level up
void UMainAbilitySystemComponent::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	if (GetAvatarActor()->Implements<UInteractionInterface>())
	{
		if (IInteractionInterface::Execute_GetAttributePoint(GetAvatarActor()) > 0)
		{
			ServerUpgradeAttribute(AttributeTag);
		}
	}
}

void UMainAbilitySystemComponent::ServerUpgradeAttribute_Implementation(const FGameplayTag& AttributeTag)
{
	FGameplayEventData Payload;
	Payload.EventTag = AttributeTag;
	Payload.EventMagnitude = 1.f;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(), AttributeTag, Payload);
	if (GetAvatarActor()->Implements<UInteractionInterface>())
	{
		IInteractionInterface::Execute_AddToAttributePoints(GetAvatarActor(), -1);
	}
}
