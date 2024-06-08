// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MainAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "DarkUnitGameplayTags.h"

UMainAttributeSet::UMainAttributeSet()
{
	const FDarkUnitGameplayTags& GameplayTags = FDarkUnitGameplayTags::Get();
	// Primary
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Endurance, GetEnduranceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Faith, GetFaithAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resolve, GetResolveAttribute);

	// Additional
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxStamina, GetMaxStaminaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defense, GetDefenseAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MagicDefense, GetMagicDefenseAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CurseResistance, GetCurseResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_StatusEffectResistance, GetStatusEffectResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Evasion, GetEvasionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_StaminaRecoveryRate, GetStaminaRecoveryRateAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealingEffectiveness, GetHealingEffectivenessAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ControlOverCurses, GetControlOverCursesAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HolyDamageResistance, GetHolyDamageResistanceAttribute);

	// Damage Types
	TagsToAttributes.Add(GameplayTags.Attributes_Damage_Physical, GetPhysicalDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Damage_Strength, GetStrengthDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Damage_Dexterity, GetDexterityDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Damage_Magic, GetMagicDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Damage_Holy, GetHolyDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Damage_Curse, GetCurseDamageAttribute);

	// Status types
	TagsToAttributes.Add(GameplayTags.Status_Slash, GetSlashStatusAttribute);
	TagsToAttributes.Add(GameplayTags.Status_Pierce, GetPierceStatusAttribute);
	TagsToAttributes.Add(GameplayTags.Status_Blunt, GetBluntStatusAttribute);
	TagsToAttributes.Add(GameplayTags.Status_Fire, GetFireStatusAttribute);
	TagsToAttributes.Add(GameplayTags.Status_Ice, GetIceStatusAttribute);
	TagsToAttributes.Add(GameplayTags.Status_Lightning, GetLightningStatusAttribute);
	TagsToAttributes.Add(GameplayTags.Status_Dark, GetDarkStatusAttribute);
	TagsToAttributes.Add(GameplayTags.Status_Poison, GetPoisonStatusAttribute);	
}
//Replication
void UMainAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Faith, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Resolve, COND_None, REPNOTIFY_Always);

	// Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MagicDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, CurseResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, StatusEffectResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Evasion, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, StaminaRecoveryRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, HealingEffectiveness, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, ControlOverCurses, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, HolyDamageResistance, COND_None, REPNOTIFY_Always);

	// Damage Types
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, PhysicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, StrengthDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DexterityDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MagicDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, HolyDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, CurseDamage, COND_None, REPNOTIFY_Always);

	// Status types
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, SlashStatus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, PierceStatus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, BluntStatus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, FireStatus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, IceStatus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, LightningStatus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, DarkStatus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, PoisonStatus, COND_None, REPNOTIFY_Always);
}
//Pre attribute changing
void UMainAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	
	
}



void UMainAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect(owner)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				// Owner PlayerController
				Props.SourceController = Pawn->GetController();
			}
			if (Props.SourceController)
			{
				// Owner Character
				Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
			}
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}	
}

void UMainAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxStamina()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage >=0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			const bool bFatal = NewHealth <= 0.f;
			if (!bFatal)
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FDarkUnitGameplayTags::Get().Effect_HitReactSmall);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
		}
	}
}



//Primary Attributes
//Vigor
// Vigor
void UMainAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Vigor, OldVigor);
}
// Endurance
void UMainAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Endurance, OldEndurance);
}
// Strength
void UMainAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Strength, OldStrength);
}
// Dexterity
void UMainAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Dexterity, OldDexterity);
}
// Intelligence
void UMainAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Intelligence, OldIntelligence);
}
// Faith
void UMainAttributeSet::OnRep_Faith(const FGameplayAttributeData& OldFaith) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Faith, OldFaith);
}
// Resolve
void UMainAttributeSet::OnRep_Resolve(const FGameplayAttributeData& OldResolve) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Resolve, OldResolve);
}


//
// Secondary
// Health
void UMainAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Health, OldHealth);
}

void UMainAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MaxHealth, OldMaxHealth);
}
//Stamina
void UMainAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Stamina, OldStamina);
}

void UMainAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MaxStamina, OldMaxStamina);
}
// Mana Points (MP)
void UMainAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Mana, OldMana);
}
// Mana Points (MP)
void UMainAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MaxMana, OldMaxMana);
}

void UMainAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Defense, OldDefense);
}

// Magic Defense
void UMainAttributeSet::OnRep_MagicDefense(const FGameplayAttributeData& OldMagicDefense) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MagicDefense, OldMagicDefense);
}
// Curse Resistance
void UMainAttributeSet::OnRep_CurseResistance(const FGameplayAttributeData& OldCurseResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, CurseResistance, OldCurseResistance);
}
// Status Effect Resistance
void UMainAttributeSet::OnRep_StatusEffectResistance(const FGameplayAttributeData& OldStatusEffectResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, StatusEffectResistance, OldStatusEffectResistance);
}
// Evasion
void UMainAttributeSet::OnRep_Evasion(const FGameplayAttributeData& OldEvasion) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, Evasion, OldEvasion);
}
// Stamina Recovery Rate
void UMainAttributeSet::OnRep_StaminaRecoveryRate(const FGameplayAttributeData& OldStaminaRecoveryRate) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, StaminaRecoveryRate, OldStaminaRecoveryRate);
}
// Healing Effectiveness
void UMainAttributeSet::OnRep_HealingEffectiveness(const FGameplayAttributeData& OldHealingEffectiveness) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, HealingEffectiveness, OldHealingEffectiveness);
}
// Control Over Curses
void UMainAttributeSet::OnRep_ControlOverCurses(const FGameplayAttributeData& OldControlOverCurses) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, ControlOverCurses, OldControlOverCurses);
}
// Holy Damage Resistance
void UMainAttributeSet::OnRep_HolyDamageResistance(const FGameplayAttributeData& OldHolyDamageResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, HolyDamageResistance, OldHolyDamageResistance);
}

// Damage Types
// Physical Damage
void UMainAttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, PhysicalDamage, OldPhysicalDamage);
}
void UMainAttributeSet::OnRep_StrengthDamage(const FGameplayAttributeData& OldStrengthDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, StrengthDamage, OldStrengthDamage);
}
void UMainAttributeSet::OnRep_DexterityDamage(const FGameplayAttributeData& OldDexterityDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DexterityDamage, OldDexterityDamage);
}
// Magic Damage
void UMainAttributeSet::OnRep_MagicDamage(const FGameplayAttributeData& OldMagicDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, MagicDamage, OldMagicDamage);
}
// Holy Damage
void UMainAttributeSet::OnRep_HolyDamage(const FGameplayAttributeData& OldHolyDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, HolyDamage, OldHolyDamage);
}
// Curse Damage
void UMainAttributeSet::OnRep_CurseDamage(const FGameplayAttributeData& OldCurseDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, CurseDamage, OldCurseDamage);
}


//
// Status types
// Slash Damage
void UMainAttributeSet::OnRep_SlashStatus(const FGameplayAttributeData& OldSlashStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, SlashStatus, OldSlashStatus);
}
// Pierce Status
void UMainAttributeSet::OnRep_PierceStatus(const FGameplayAttributeData& OldPierceStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, PierceStatus, OldPierceStatus);
}
// Blunt Status
void UMainAttributeSet::OnRep_BluntStatus(const FGameplayAttributeData& OldBluntStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, BluntStatus, OldBluntStatus);
}
// Poison Status
void UMainAttributeSet::OnRep_PoisonStatus(const FGameplayAttributeData& OldPoisonStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, PoisonStatus, OldPoisonStatus);
}
// Fire Status
void UMainAttributeSet::OnRep_FireStatus(const FGameplayAttributeData& OldFireStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, FireStatus, OldFireStatus);
}
// Ice Status
void UMainAttributeSet::OnRep_IceStatus(const FGameplayAttributeData& OldIceStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, IceStatus, OldIceStatus);
}
// Lightning Status
void UMainAttributeSet::OnRep_LightningStatus(const FGameplayAttributeData& OldLightningStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, LightningStatus, OldLightningStatus);
}
// Dark Status
void UMainAttributeSet::OnRep_DarkStatus(const FGameplayAttributeData& OldDarkStatus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet, DarkStatus, OldDarkStatus);
}