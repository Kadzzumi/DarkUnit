// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DarkUnitDamageGA.h"
#include "EnemyWeaponSpecAbility.generated.h"

class AEnemyWeaponBase;
/**
 * 
 */
UCLASS()
class DARKUNIT_API UEnemyWeaponSpecAbility : public UDarkUnitDamageGA
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AEnemyWeaponBase> WeaponClass;


};
