// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WeaponSpecAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Character/Player/PlayerCharacterBase.h"


void UWeaponSpecAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;
	// Get the Hand Socket
	APlayerCharacterBase* Player = Cast<APlayerCharacterBase>(GetAvatarActorFromActorInfo());
	if (Player)
	{
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent((GetAvatarActorFromActorInfo()));
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		// Weapon
		AWeaponBase* Weapon = Cast<AWeaponBase>(Player->EquippedWeapon);
		
		// Capture Attributes
		const UMainAttributeSet* AttributeSet = Cast<UMainAttributeSet>(SourceASC->GetAttributeSet(UMainAttributeSet::StaticClass()));
		
		const float StrengthValue = Weapon->GetTierValue(Weapon->StrengthDamageEff) * AttributeSet->GetStrength();
		const float DexterityValue = Weapon->GetTierValue(Weapon->DexterityDamageEff) * AttributeSet->GetDexterity();
		const float IntelligenceValue = Weapon->GetTierValue(Weapon->IntelligenceDamageEff) * AttributeSet->GetIntelligence();
		const float FaithValue = Weapon->GetTierValue(Weapon->FaithDamageEff) * AttributeSet->GetFaith();
		const float ResolveValue = Weapon->GetTierValue(Weapon->CurseDamageEff) * AttributeSet->GetResolve();

		//Tag For the Damage
		const FDarkUnitGameplayTags GameplayTags = FDarkUnitGameplayTags::Get();
		//Damage

		float ScaledDamage = Weapon->PhysicalDamage + StrengthValue + DexterityValue + IntelligenceValue + FaithValue + ResolveValue;
		// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("FireBolt Damage: %f"), ScaledDamage));
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Damage_Physical, ScaledDamage);
			
		Weapon->DamageEffectSpecHandle = SpecHandle;
	}
	K2_EndAbility();
}
