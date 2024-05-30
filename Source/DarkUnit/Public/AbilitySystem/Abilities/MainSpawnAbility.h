// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DarkUnitGameplayAbility.h"
#include "MainSpawnAbility.generated.h"

class AWeaponBase;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class DARKUNIT_API UMainSpawnAbility : public UDarkUnitGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWeaponBase> WeaponClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
