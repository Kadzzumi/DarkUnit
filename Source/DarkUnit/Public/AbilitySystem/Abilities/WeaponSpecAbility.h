// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DarkUnitDamageGA.h"
#include "WeaponSpecAbility.generated.h"

class APlayerWeaponBase;
/**
 * 
 */
UCLASS()
class DARKUNIT_API UWeaponSpecAbility : public UDarkUnitDamageGA
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;;
	void UpdateWeaponSpec(APlayerWeaponBase* DefaultWeapon) const;
};
