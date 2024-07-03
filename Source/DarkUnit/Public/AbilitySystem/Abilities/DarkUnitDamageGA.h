// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DarkUnitGameplayAbility.h"
#include "DarkUnitDamageGA.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UDarkUnitDamageGA : public UDarkUnitGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
public:
	UFUNCTION(BlueprintCallable, Category="Attack Collision")
	virtual void SetCollisions(int32 Index);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
