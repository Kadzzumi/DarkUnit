// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 * Singleton containing Native GameplayTags
 */

struct FDarkUnitGameplayTags
{
public:
	
	static const FDarkUnitGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	//Primary Attributes
	FGameplayTag Attributes_Secondary_Vigor;
	FGameplayTag Attributes_Secondary_Endurance;
	FGameplayTag Attributes_Secondary_Defense;
	FGameplayTag Attributes_Secondary_Strength;
	FGameplayTag Attributes_Secondary_Agility;
	FGameplayTag Attributes_Secondary_Penetration;

	//SECONDARY Attributes
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_StaminaRecovery;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_Block;
	FGameplayTag Attributes_Secondary_PhysDamage;
	FGameplayTag Attributes_Secondary_CritDamage;
	FGameplayTag Attributes_Secondary_AttackSpeed;
	FGameplayTag Attributes_Secondary_MovementSpeed;
	FGameplayTag Attributes_Secondary_Impulse;
	FGameplayTag Attributes_Secondary_StunChance;
	
	
 
protected:
 
private:
	static FDarkUnitGameplayTags GameplayTags;
};
