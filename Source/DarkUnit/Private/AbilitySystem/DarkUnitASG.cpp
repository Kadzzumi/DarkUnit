// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DarkUnitASG.h"

#include "DarkUnitAbilityTypes.h"

FGameplayEffectContext* UDarkUnitASG::AllocGameplayEffectContext() const
{
	return new FDarkUnitGameplayEffectContext();
}
