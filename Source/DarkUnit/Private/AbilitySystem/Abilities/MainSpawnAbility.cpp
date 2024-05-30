// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MainSpawnAbility.h"

#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>

#include "Engine/SkeletalMeshSocket.h"
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
			const FTransform SpawnTransform = CombatInterface->GetCombatSocketTransform();
			AWeaponBase* DefaultWeapon = GetWorld()->SpawnActorDeferred<AWeaponBase>(WeaponClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent((GetAvatarActorFromActorInfo()));
			const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
			
			DefaultWeapon->DamageEffectSpecHandle = SpecHandle;
			DefaultWeapon->FinishSpawning(SpawnTransform);
			// Attach the weapon
			CombatInterface->SetWeaponAttachment(DefaultWeapon);
			
		}
	}
}
