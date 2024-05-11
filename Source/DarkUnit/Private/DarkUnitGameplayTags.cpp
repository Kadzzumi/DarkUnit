// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkUnitGameplayTags.h"
#include "GameplayTagsManager.h"
FDarkUnitGameplayTags FDarkUnitGameplayTags::GameplayTags;

void FDarkUnitGameplayTags::InitializeNativeGameplayTags()
{

	//Secondary attribute tags
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Improves Health of the Character. Gives more survivability"));
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxStamina"), FString("Improves Stamina of the Character. Gives more Ability to do advanced movement"));
	GameplayTags.Attributes_Secondary_StaminaRecovery = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StaminaRecovery"), FString("Recovers Stamina Faster"));
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Improves Defense of the Character. Gives more survivability"));
	GameplayTags.Attributes_Secondary_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Block"), FString("Blocks the Impulse if it is high enough"));
	GameplayTags.Attributes_Secondary_PhysDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.PhysDamage"), FString("Improves damage"));
	GameplayTags.Attributes_Secondary_CritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritDamage"), FString("Improves damage when used charged attack"));
	GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackSpeed"), FString("Improves attack speed of the player"));
	GameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MovementSpeed"), FString("Improves max movement speed"));
	GameplayTags.Attributes_Secondary_Impulse = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Impulse"), FString("Improves Impulse"));
	GameplayTags.Attributes_Secondary_StunChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StunChance"), FString("Stun chance is improved"));

	//Primary attributes
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Improves health of the character"));
	GameplayTags.Attributes_Primary_Endurance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Endurance"), FString("Improves endurance of the character"));
	GameplayTags.Attributes_Primary_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Defense"), FString("Improves defense of the character"));
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Improves strength of the character"));
	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Agility"), FString("Improves agility of the character"));
	GameplayTags.Attributes_Primary_Penetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Penetration"), FString("Improves penetration of the character"));
}
