// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FDarkUnitGameplayTags
{
public:
	
	static const FDarkUnitGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	//Primary Attributes
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Endurance;
	FGameplayTag Attributes_Primary_Defense;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Penetration;
	// Secondary
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

	//Inputs tags
	FGameplayTag InputTag_Attack;
	FGameplayTag InputTag_Block;
	FGameplayTag InputTag_SkillA;
	FGameplayTag InputTag_SkillB;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Dodge;
	FGameplayTag InputTag_Inventory;
	FGameplayTag InputTag_SwapWeapon;
	FGameplayTag InputTag_SwapSecondaryWeapon;
	FGameplayTag InputTag_SwapItem;
	FGameplayTag InputTag_OpenMap;
	FGameplayTag InputTag_Interact;
	FGameplayTag InputTag_AttributeMenu;
	
private:
	static FDarkUnitGameplayTags GameplayTags;
};
