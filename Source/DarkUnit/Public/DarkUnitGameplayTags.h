// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FDarkUnitGameplayTags
{
public:
	
	static const FDarkUnitGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	// Primary Attributes
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Endurance;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Faith;
	FGameplayTag Attributes_Primary_Resolve;

	// Additional Attributes
	FGameplayTag Attributes_Secondary_MaxHealth;             // Health Points (HP)
	FGameplayTag Attributes_Secondary_MaxStamina;            // Stamina Points (SP)
	FGameplayTag Attributes_Secondary_MaxMana;               // Mana Points (MP)
	
	// Resistances and Evasion
	FGameplayTag Attributes_Secondary_Focus;					// Focus
	FGameplayTag Attributes_Secondary_Evasion;                  // Evasion
	FGameplayTag Attributes_Secondary_StaminaRecoveryRate;      // Stamina Recovery Rate
	FGameplayTag Attributes_Secondary_HealingEffectiveness;     // Healing Effectiveness
	FGameplayTag Attributes_Secondary_ControlOverCurses;        // Control Over Curses
	
	//Defenses
	FGameplayTag Attributes_Resistances_Defense;                  // Physical Defense
	FGameplayTag Attributes_Resistances_FireResistance;           // Physical Defense
	FGameplayTag Attributes_Resistances_IceResistance;            // Physical Defense
	FGameplayTag Attributes_Resistances_LightningResistance;      // Physical Defense
	FGameplayTag Attributes_Resistances_MagicDefense;             // Magic and Ice Defense
	FGameplayTag Attributes_Resistances_HolyDamageResistance;     // Holy, Fire and Lightning Damage Resistance
	FGameplayTag Attributes_Resistances_CurseResistance;          // Curse Resistance
	
	FGameplayTag Attributes_Resistances_StatusEffectResistance;   // Status Effect Resistance

	
	// Damage Types
	FGameplayTag Attributes_Damage_WeaponDamage;
	FGameplayTag Attributes_Damage_Physical;
	FGameplayTag Attributes_Damage_Fire;
	FGameplayTag Attributes_Damage_Ice;
	FGameplayTag Attributes_Damage_Lightning;
	FGameplayTag Attributes_Damage_Magic;
	FGameplayTag Attributes_Damage_Holy;
	FGameplayTag Attributes_Damage_Curse;

	//Status Effects
	FGameplayTag Status_Slash;
	FGameplayTag Status_Pierce;
	FGameplayTag Status_Blunt;
	FGameplayTag Status_Burn;
	FGameplayTag Status_Frost;
	FGameplayTag Status_Strike;
	FGameplayTag Status_Blight;
	FGameplayTag Status_Poison;

	FGameplayTag Effect_HitReactSmall;
	
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
	FGameplayTag InputTag_SpawnDefaultWeapon;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	//
	FGameplayTag GA_SetWeaponSpecHandle;

private:
	static FDarkUnitGameplayTags GameplayTags;
};
