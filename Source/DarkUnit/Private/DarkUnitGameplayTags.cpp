// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkUnitGameplayTags.h"
#include "GameplayTagsManager.h"
FDarkUnitGameplayTags FDarkUnitGameplayTags::GameplayTags;

void FDarkUnitGameplayTags::InitializeNativeGameplayTags()
{
	// Primary attributes
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Improves health of the character"));
	GameplayTags.Attributes_Primary_Endurance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Endurance"), FString("Improves endurance of the character"));
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Improves strength of the character"));
	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Dexterity"), FString("Improves dexterity of the character"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Improves magic power of the character"));
	GameplayTags.Attributes_Primary_Faith = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Faith"), FString("Improves faith of the character"));
	GameplayTags.Attributes_Primary_Resolve = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resolve"), FString("Improves resolve of the character"));

	// Additional attribute tags
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Improves health of the character. Gives more survivability"));
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxStamina"), FString("Improves stamina of the character. Gives more ability to perform advanced movements"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Improves mana of the character"));
	GameplayTags.Attributes_Secondary_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Defense"), FString("Improves defense of the character. Gives more survivability"));
	GameplayTags.Attributes_Secondary_MagicDefense = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicDefense"), FString("Improves magic defense of the character"));
	GameplayTags.Attributes_Secondary_CurseResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CurseResistance"), FString("Improves curse resistance of the character"));
	GameplayTags.Attributes_Secondary_StatusEffectResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StatusEffectResistance"), FString("Improves resistance to status effects"));
	GameplayTags.Attributes_Secondary_Evasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Evasion"), FString("Improves evasion"));
	GameplayTags.Attributes_Secondary_StaminaRecoveryRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StaminaRecoveryRate"), FString("Recovers stamina faster"));
	GameplayTags.Attributes_Secondary_HealingEffectiveness = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealingEffectiveness"), FString("Improves healing effectiveness"));
	GameplayTags.Attributes_Secondary_ControlOverCurses = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ControlOverCurses"), FString("Improves control over curses"));
	GameplayTags.Attributes_Secondary_HolyDamageResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HolyDamageResistance"), FString("Improves resistance to holy damage"));

	// Damage Types
	GameplayTags.Attributes_Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Physical"), FString("Physical damage"));
	GameplayTags.Attributes_Damage_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Strength"), FString("Strength damage"));
	GameplayTags.Attributes_Damage_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Dexterity"), FString("Dexterity damage"));
	GameplayTags.Attributes_Damage_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Magic"), FString("Magic damage"));
	GameplayTags.Attributes_Damage_Holy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Holy"), FString("Holy damage"));
	GameplayTags.Attributes_Damage_Curse = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Curse"), FString("Curse damage"));

	// Status types
	GameplayTags.Status_Slash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Status.Slash"), FString("Slash Status"));
	GameplayTags.Status_Pierce = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Status.Pierce"), FString("Pierce Status"));
	GameplayTags.Status_Blunt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Status.Blunt"), FString("Blunt Status"));
	GameplayTags.Status_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Fire"), FString("Fire Status"));
	GameplayTags.Status_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Ice"), FString("Ice Status"));
	GameplayTags.Status_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Lightning"), FString("Lightning Status"));
	GameplayTags.Status_Dark = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Dark"), FString("Dark Status"));
	GameplayTags.Status_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Poison"), FString("Poison Status"));

	// Effects
	GameplayTags.Effect_HitReactSmall = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effect.HitReactSmall"), FString("Hit Reaction slight"));

	
	//Input Tags
	GameplayTags.InputTag_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Attack"), FString("Triggers the attack action"));
	GameplayTags.InputTag_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Block"), FString("Triggers the block action"));
	GameplayTags.InputTag_SkillA = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SkillA"), FString("Activates skill A"));
	GameplayTags.InputTag_SkillB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SkillB"), FString("Activates skill B"));
	GameplayTags.InputTag_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Jump"), FString("Triggers the jump action"));
	GameplayTags.InputTag_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Dodge"), FString("Triggers the dodge action"));
	GameplayTags.InputTag_Inventory = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Inventory"), FString("Opens the inventory menu"));
	GameplayTags.InputTag_SwapWeapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SwapWeapon"), FString("Swaps the current weapon"));
	GameplayTags.InputTag_SwapSecondaryWeapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SwapSecondaryWeapon"), FString("Swaps the current Secondary weapon"));
	GameplayTags.InputTag_SwapItem = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SwapItem"), FString("Swaps the current item"));
	GameplayTags.InputTag_OpenMap = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.OpenMap"), FString("Opens the map"));
	GameplayTags.InputTag_Interact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Interact"), FString("Inteact key"));
	GameplayTags.InputTag_AttributeMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.AttributeMenu"), FString("Attribute Menu key"));
	GameplayTags.InputTag_SpawnDefaultWeapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SpawnDefaultWeapon"), FString("Spawns Weapon"));

}
