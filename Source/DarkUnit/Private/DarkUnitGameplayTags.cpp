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
	GameplayTags.Attributes_Secondary_Evasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Evasion"), FString("Improves evasion"));
	GameplayTags.Attributes_Secondary_StaminaRecoveryRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StaminaRecoveryRate"), FString("Recovers stamina faster"));
	GameplayTags.Attributes_Secondary_HealingEffectiveness = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealingEffectiveness"), FString("Improves healing effectiveness"));
	GameplayTags.Attributes_Secondary_ControlOverCurses = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ControlOverCurses"), FString("Improves control over curses"));
	GameplayTags.Attributes_Secondary_Focus = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Focus"), FString("Improves Focus"));

	// Defenses
	GameplayTags.Attributes_Resistances_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.Defense"), FString("Improves physical defense of the character. Gives more survivability"));
	GameplayTags.Attributes_Resistances_FireResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.FireResistance"), FString("Improves resistance to fire damage. Increases survivability against fire attacks"));
	GameplayTags.Attributes_Resistances_IceResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.IceResistance"), FString("Improves resistance to ice damage. Increases survivability against ice attacks"));
	GameplayTags.Attributes_Resistances_LightningResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.LightningResistance"), FString("Improves resistance to lightning damage. Increases survivability against lightning attacks"));
	GameplayTags.Attributes_Resistances_MagicDefense = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.MagicDefense"), FString("Improves magic and ice defense of the character. Provides better protection against magical and ice-based attacks"));
	GameplayTags.Attributes_Resistances_HolyDamageResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.HolyDamageResistance"), FString("Improves resistance to holy, fire, and lightning damage. Provides comprehensive protection against these elements"));
	GameplayTags.Attributes_Resistances_CurseResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.CurseResistance"), FString("Improves resistance to curses. Reduces the impact of curse-based attacks"));
	GameplayTags.Attributes_Resistances_StatusEffectResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistances.StatusEffectResistance"), FString("Improves resistance to status effects. Reduces the duration and impact of status effects"));

	// Damage Types
	GameplayTags.Attributes_Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Physical"), FString("Physical damage"));
	GameplayTags.Attributes_Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Fire"), FString("Fire damage"));
	GameplayTags.Attributes_Damage_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Ice"), FString("Ice damage"));
	GameplayTags.Attributes_Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Lightning"), FString("Lightning damage"));
	GameplayTags.Attributes_Damage_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Magic"), FString("Magic damage"));
	GameplayTags.Attributes_Damage_Holy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Holy"), FString("Holy damage"));
	GameplayTags.Attributes_Damage_Curse = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Damage.Curse"), FString("Curse damage"));


	// TMap for the damage and its resistance
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Attributes_Damage_Physical, GameplayTags.Attributes_Resistances_Defense);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Attributes_Damage_Fire, GameplayTags.Attributes_Resistances_FireResistance);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Attributes_Damage_Ice, GameplayTags.Attributes_Resistances_IceResistance);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Attributes_Damage_Lightning, GameplayTags.Attributes_Resistances_LightningResistance);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Attributes_Damage_Magic, GameplayTags.Attributes_Resistances_MagicDefense);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Attributes_Damage_Holy, GameplayTags.Attributes_Resistances_HolyDamageResistance);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Attributes_Damage_Curse, GameplayTags.Attributes_Resistances_CurseResistance);
	
	// Status types
	GameplayTags.Status_Slash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Slash"), FString("Slash Status"));
	GameplayTags.Status_Pierce = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Pierce"), FString("Pierce Status"));
	GameplayTags.Status_Blunt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Blunt"), FString("Blunt Status"));
	GameplayTags.Status_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Burn"), FString("Fire Status"));
	GameplayTags.Status_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Frost"), FString("Ice Status"));
	GameplayTags.Status_Strike = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Strike"), FString("Lightning Status"));
	GameplayTags.Status_Blight = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Blight"), FString("Dark Status"));
	GameplayTags.Status_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Status.Poison"), FString("Poison Status"));
	
	// Effects
	GameplayTags.Effect_HitReactSmall = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effect.HitReactSmall"), FString("Hit Reaction slight"));

	// Essence Bond
	GameplayTags.EssenceBond_CircleSwing = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EssenceBond.CircleSwing"), FString("EssenceBond"));
	GameplayTags.EssenceBond_ForwardPoke = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EssenceBond.ForwardPoke"), FString("EssenceBond"));
	GameplayTags.EssenceBond_UpwardPoke = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EssenceBond.UpwardPoke"), FString("EssenceBond"));
	
	// Sigil
	GameplayTags.Sigil_BluntResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sigil.BluntResistance"), FString("EssenceBond"));
	
	// Spells
	GameplayTags.Conjuration_Fire_FireBall = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Conjuration.Fire.FireBall"), FString("Fire Ball"));
	
	// Cool-downs
	GameplayTags.CD_EssenceBond_Low = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CD.EssenceBond.Low"), FString("Low Cooldown"));
	GameplayTags.CD_Sigil_Low = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CD.Sigil.Low"), FString("Low Cooldown"));
	GameplayTags.CD_Conjuration_Low = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CD.Conjuration.Low"), FString("Low Cooldown"));

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

	//
	GameplayTags.GA_SetWeaponSpecHandle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GA.SetWeaponSpecHandle"), FString("Spawns Weapon Spec Handle"));

	//
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"), FString("Get the incoming XP value"));

	
	// Weapon Socket Montage tags
	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.Weapon"), FString(""));
	GameplayTags.Montage_Attack_WeaponBack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.WeaponBack"), FString(""));
	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.RightHand"), FString(""));
	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.LeftHand"), FString(""));

	
}
