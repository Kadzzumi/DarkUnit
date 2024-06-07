// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MainAttributeSet.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(): SourceCharacter(nullptr), TargetCharacter(nullptr)
	{
	}

	FGameplayEffectContextHandle EffectContextHandle;
	// Owner
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter;
	
	// Target
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter;
	
};

// typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class DARKUNIT_API UMainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMainAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	//
	//Vital Attributes
	//
	//
// Primary Attributes
//
	// Vigor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Vigor);
	
	// Endurance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Endurance, Category = "Primary Attributes")
	FGameplayAttributeData Endurance;
	UFUNCTION()
	void OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Endurance);
	
	// Strength
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Strength);
	
	// Dexterity
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Dexterity);
	
	// Intelligence
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Intelligence);
	
	// Faith
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Faith, Category = "Primary Attributes")
	FGameplayAttributeData Faith;
	UFUNCTION()
	void OnRep_Faith(const FGameplayAttributeData& OldFaith) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Faith);
	
	// Resolve
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resolve, Category = "Primary Attributes")
	FGameplayAttributeData Resolve;
	UFUNCTION()
	void OnRep_Resolve(const FGameplayAttributeData& OldResolve) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Resolve);

//
// Vital Attributes
//
	// Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxHealth);
	
	// Stamina
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Stamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxStamina);
	
	// Mana Points (MP)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Mana);

		
	// Mana Points (MP)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxMana);
	
	// Defense
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Vital Attributes")
	FGameplayAttributeData Defense;
	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldDefense) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Defense);
	
	// Magic Defense
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDefense, Category = "Vital Attributes")
	FGameplayAttributeData MagicDefense;
	UFUNCTION()
	void OnRep_MagicDefense(const FGameplayAttributeData& OldMagicDefense) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MagicDefense);
	
	// Curse Resistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurseResistance, Category = "Vital Attributes")
	FGameplayAttributeData CurseResistance;
	UFUNCTION()
	void OnRep_CurseResistance(const FGameplayAttributeData& OldCurseResistance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, CurseResistance);
	
	// Status Effect Resistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StatusEffectResistance, Category = "Vital Attributes")
	FGameplayAttributeData StatusEffectResistance;
	UFUNCTION()
	void OnRep_StatusEffectResistance(const FGameplayAttributeData& OldStatusEffectResistance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, StatusEffectResistance);
	
	// Evasion
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Evasion, Category = "Vital Attributes")
	FGameplayAttributeData Evasion;
	UFUNCTION()
	void OnRep_Evasion(const FGameplayAttributeData& OldEvasion) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Evasion);
	
	// Stamina Recovery Rate
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRecoveryRate, Category = "Vital Attributes")
	FGameplayAttributeData StaminaRecoveryRate;
	UFUNCTION()
	void OnRep_StaminaRecoveryRate(const FGameplayAttributeData& OldStaminaRecoveryRate) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, StaminaRecoveryRate);

	// Healing Effectiveness
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealingEffectiveness, Category = "Vital Attributes")
	FGameplayAttributeData HealingEffectiveness;
	UFUNCTION()
	void OnRep_HealingEffectiveness(const FGameplayAttributeData& OldHealingEffectiveness) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, HealingEffectiveness);

	// Control Over Curses
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ControlOverCurses, Category = "Vital Attributes")
	FGameplayAttributeData ControlOverCurses;
	UFUNCTION()
	void OnRep_ControlOverCurses(const FGameplayAttributeData& OldControlOverCurses) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, ControlOverCurses);

	// Holy Damage Resistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HolyDamageResistance, Category = "Vital Attributes")
	FGameplayAttributeData HolyDamageResistance;
	UFUNCTION()
	void OnRep_HolyDamageResistance(const FGameplayAttributeData& OldHolyDamageResistance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, HolyDamageResistance);

	// Damage Types
	// Physical Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamage, Category = "Damage Types")
	FGameplayAttributeData PhysicalDamage;
	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, PhysicalDamage);

	// Strength Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StrengthDamage, Category = "Damage Types")
	FGameplayAttributeData StrengthDamage;
	UFUNCTION()
	void OnRep_StrengthDamage(const FGameplayAttributeData& OldStrengthDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, StrengthDamage);

	// Dexterity Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DexterityDamage, Category = "Damage Types")
	FGameplayAttributeData DexterityDamage;
	UFUNCTION()
	void OnRep_DexterityDamage(const FGameplayAttributeData& OldDexterityDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, DexterityDamage);
	
	// Magic Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamage, Category = "Damage Types")
	FGameplayAttributeData MagicDamage;
	UFUNCTION()
	void OnRep_MagicDamage(const FGameplayAttributeData& OldMagicDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MagicDamage);

	// Holy Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HolyDamage, Category = "Damage Types")
	FGameplayAttributeData HolyDamage;
	UFUNCTION()
	void OnRep_HolyDamage(const FGameplayAttributeData& OldHolyDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, HolyDamage);
	
	// Curse Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurseDamage, Category = "Damage Types")
	FGameplayAttributeData CurseDamage;
	UFUNCTION()
	void OnRep_CurseDamage(const FGameplayAttributeData& OldCurseDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, CurseDamage);

	
	//
	//Status effects
	// Slash Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SlashStatus, Category = "Status Types")
	FGameplayAttributeData SlashStatus;
	UFUNCTION()
	void OnRep_SlashStatus(const FGameplayAttributeData& OldSlashStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, SlashStatus);

	// Pierce Status
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PierceStatus, Category = "Status Types")
	FGameplayAttributeData PierceStatus;
	UFUNCTION()
	void OnRep_PierceStatus(const FGameplayAttributeData& OldPierceStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, PierceStatus);

	// Poison Status
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PoisonStatus, Category = "Status Types")
	FGameplayAttributeData PoisonStatus;
	UFUNCTION()
	void OnRep_PoisonStatus(const FGameplayAttributeData& OldPoisonStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, PoisonStatus);

	// Dark Status
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DarkStatus, Category = "Status Types")
	FGameplayAttributeData DarkStatus;
	UFUNCTION()
	void OnRep_DarkStatus(const FGameplayAttributeData& OldDarkStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, DarkStatus);
	
	// Fire Status
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireStatus, Category = "Status Types")
	FGameplayAttributeData FireStatus;
	UFUNCTION()
	void OnRep_FireStatus(const FGameplayAttributeData& OldFireStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, FireStatus);

	// Ice Status
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IceStatus, Category = "Status Types")
	FGameplayAttributeData IceStatus;
	UFUNCTION()
	void OnRep_IceStatus(const FGameplayAttributeData& OldIceStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, IceStatus);

	// Lightning Status
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningStatus, Category = "Status Types")
	FGameplayAttributeData LightningStatus;
	UFUNCTION()
	void OnRep_LightningStatus(const FGameplayAttributeData& OldLightningStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, LightningStatus);
	
	// Blunt Status
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BluntStatus, Category = "Status Types")
	FGameplayAttributeData BluntStatus;
	UFUNCTION()
	void OnRep_BluntStatus(const FGameplayAttributeData& OldBluntStatus) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, BluntStatus);

	//
	//Meta Attributes
	UPROPERTY(BlueprintReadOnly, Category="MetaAttributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, IncomingDamage);
	
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	
};
