// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WeaponSpecAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Actor/Weapon/Player/PlayerWeaponBase.h"
#include "Character/Player/PlayerCharacterBase.h"
#include "PlayerController/MainPlayerState.h"


void UWeaponSpecAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
   	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
  	const bool bIsServer = HasAuthority(&ActivationInfo);
  	if (!bIsServer) return;
  	// Get the Hand Socket
	if (APlayerCharacterBase* PlayerCharacter = Cast<APlayerCharacterBase>(GetAvatarActorFromActorInfo()))
	{
		const AMainPlayerState* PlayerState = Cast<AMainPlayerState>(PlayerCharacter->GetPlayerState());
		if (PlayerState && PlayerState->EquippedWeapon1 != nullptr)
		{
			UpdateWeaponSpec(PlayerState->EquippedWeapon1);
		}
		if (PlayerState && PlayerState->EquippedWeapon2 != nullptr)
		{
			UpdateWeaponSpec(PlayerState->EquippedWeapon2);
		}
	}
   	K2_EndAbility();
}

void UWeaponSpecAbility::UpdateWeaponSpec(APlayerWeaponBase* DefaultWeapon) const
{
		{
			//Interface Values
	            	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent((GetAvatarActorFromActorInfo()));
        		
        			// Effect Context Handle
        			FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
        			EffectContextHandle.SetAbility(this);
        			EffectContextHandle.AddSourceObject(DefaultWeapon);
        			TArray<TWeakObjectPtr<AActor>> Actors;
        			Actors.Add(DefaultWeapon);
        			EffectContextHandle.AddActors(Actors);
        			FHitResult HitResult;
        			EffectContextHandle.AddHitResult(HitResult);
        		
	            	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	            	// Capture Attributes
	            	const UMainAttributeSet* AttributeSet = Cast<UMainAttributeSet>(SourceASC->GetAttributeSet(UMainAttributeSet::StaticClass()));

        			//Damage Types
	            	const float StrengthValue = DefaultWeapon->GetTierValue(DefaultWeapon->StrengthDamageEff) * AttributeSet->GetStrength();
	            	const float DexterityValue = DefaultWeapon->GetTierValue(DefaultWeapon->DexterityDamageEff) * AttributeSet->GetDexterity();
	            	const float IntelligenceValue = DefaultWeapon->GetTierValue(DefaultWeapon->IntelligenceDamageEff) * AttributeSet->GetIntelligence();
	            	const float FaithValue = DefaultWeapon->GetTierValue(DefaultWeapon->FaithDamageEff) * AttributeSet->GetFaith();
	            	const float ResolveValue = DefaultWeapon->GetTierValue(DefaultWeapon->CurseDamageEff) * AttributeSet->GetResolve();

        			FGameplayTag WeaponDamageType = DefaultWeapon->WeaponDamageTag;

	            	//Tag For the Damage
	            	const FDarkUnitGameplayTags GameplayTags = FDarkUnitGameplayTags::Get();
	            	//Damage
        			const float ScaledDamage = DefaultWeapon->GetWeaponDamage() + (StrengthValue + DexterityValue + IntelligenceValue + FaithValue + ResolveValue) * 10;
        			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, WeaponDamageType, ScaledDamage);

	            	DefaultWeapon->DamageEffectSpecHandle = SpecHandle;
		}
}
