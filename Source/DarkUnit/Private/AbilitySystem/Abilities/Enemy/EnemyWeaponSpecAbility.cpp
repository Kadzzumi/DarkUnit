// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Enemy/EnemyWeaponSpecAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Actor/Weapon/Enemy/EnemyWeaponBase.h"
#include "Interaction/CombatInterface.h"

void UEnemyWeaponSpecAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

            AEnemyWeaponBase* DefaultWeapon = GetWorld()->SpawnActorDeferred<AEnemyWeaponBase>(WeaponClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
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

        	FGameplayTag WeaponDamageType = DefaultWeapon->WeaponDamageTag;

            //Tag For the Damage
            const FDarkUnitGameplayTags GameplayTags = FDarkUnitGameplayTags::Get();
            //Damage
        	const float ScaledDamage = DefaultWeapon->GetWeaponDamage();
        	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, WeaponDamageType, ScaledDamage);

            DefaultWeapon->DamageEffectSpecHandle = SpecHandle;
            DefaultWeapon->FinishSpawning(SpawnTransform);
            // Attach the weapon
            CombatInterface->SetWeaponAttachment(DefaultWeapon);
        }
    }
    K2_EndAbility();
}
