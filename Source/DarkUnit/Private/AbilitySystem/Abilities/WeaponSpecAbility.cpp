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
    if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
    {
        if (WeaponClass)
        {
            //Interface Values
            const FTransform SpawnTransform = CombatInterface->GetCombatSocketTransform();

            AWeaponBase* DefaultWeapon = GetWorld()->SpawnActorDeferred<AWeaponBase>(WeaponClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
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

            const float StrengthValue = DefaultWeapon->GetTierValue(DefaultWeapon->StrengthDamageEff) * AttributeSet->GetStrength();
            const float DexterityValue = DefaultWeapon->GetTierValue(DefaultWeapon->DexterityDamageEff) * AttributeSet->GetDexterity();
            const float IntelligenceValue = DefaultWeapon->GetTierValue(DefaultWeapon->IntelligenceDamageEff) * AttributeSet->GetIntelligence();
            const float FaithValue = DefaultWeapon->GetTierValue(DefaultWeapon->FaithDamageEff) * AttributeSet->GetFaith();
            const float ResolveValue = DefaultWeapon->GetTierValue(DefaultWeapon->CurseDamageEff) * AttributeSet->GetResolve();


            //Tag For the Damage
            const FDarkUnitGameplayTags GameplayTags = FDarkUnitGameplayTags::Get();
            //Damage
        	for (auto& Pair : DamageTypes)
        	{
        		const float ScaledDamage = DefaultWeapon->PhysicalDamage + (StrengthValue + DexterityValue + IntelligenceValue + FaithValue + ResolveValue) * 10;
        		const float OverallDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
        		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, OverallDamage + ScaledDamage);
        	}

            DefaultWeapon->DamageEffectSpecHandle = SpecHandle;
            
            DefaultWeapon->FinishSpawning(SpawnTransform);
            // Attach the weapon
            CombatInterface->SetWeaponAttachment(DefaultWeapon);
        }
    }
   K2_EndAbility();
}
