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

            const float ScaledDamage = DefaultWeapon->PhysicalDamage + (StrengthValue + DexterityValue + IntelligenceValue + FaithValue + ResolveValue) * 10;
            // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("FireBolt Damage: %f"), ScaledDamage));
            UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Damage_WeaponDamage, ScaledDamage);

            DefaultWeapon->DamageEffectSpecHandle = SpecHandle;
            
            DefaultWeapon->FinishSpawning(SpawnTransform);
            // Attach the weapon
            CombatInterface->SetWeaponAttachment(DefaultWeapon);
        }
    }
   K2_EndAbility();
}
