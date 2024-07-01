// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DarkUnitDamageGA.h"
#include "WeaponSpecAbility.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS()
class DARKUNIT_API UWeaponSpecAbility : public UDarkUnitDamageGA
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWeaponBase> WeaponClass;	
};
