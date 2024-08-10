// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponPickUp.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/Weapon/Player/PlayerWeaponBase.h"
#include "Character/Player/PlayerCharacterBase.h"
#include "PlayerController/MainPlayerState.h"

void AWeaponPickUp::Interact(APlayerCharacterBase* Player)
{
	if (StoredWeapon)
	{
		AMainPlayerState* MainPlayerState = Cast<AMainPlayerState>(Player->GetPlayerState());
		MainPlayerState->WeaponInventory.Add(StoredWeapon);
	}
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Player))
	{
		check(GameplayEffectClass);
		// Get Target's AbilitySystemComponent
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
	}
	Destroy();
}
