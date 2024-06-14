// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MainSpawnAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DarkUnit/Public/DarkUnitGameplayTags.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Interaction/CombatInterface.h"

void UMainSpawnAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
			float ScaledDamage = CombatInterface->CalculateOveralldDamage();
			
			AWeaponBase* DefaultWeapon = GetWorld()->SpawnActorDeferred<AWeaponBase>(WeaponClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent((GetAvatarActorFromActorInfo()));
			const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
			//Tag For the Damage
			const FDarkUnitGameplayTags GameplayTags = FDarkUnitGameplayTags::Get();
			//Damage
			ScaledDamage += Damage.GetValueAtLevel(GetAbilityLevel());
			// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("FireBolt Damage: %f"), ScaledDamage));
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Damage_Physical, ScaledDamage);
			
			DefaultWeapon->DamageEffectSpecHandle = SpecHandle;
			DefaultWeapon->FinishSpawning(SpawnTransform);
			// Attach the weapon
			CombatInterface->SetWeaponAttachment(DefaultWeapon);
		}
	}
	K2_EndAbility();
}
