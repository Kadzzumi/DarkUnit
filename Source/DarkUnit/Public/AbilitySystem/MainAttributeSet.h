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
	FEffectProperties() {}
	
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
	
//
// Primary Attributes
//
	//Vigor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Vigor);
	
	//Endurance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Endurance, Category = "Primary Attributes")
	FGameplayAttributeData Endurance;
	UFUNCTION()
	void OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Endurance);
	
	//Defense
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Primary Attributes")
	FGameplayAttributeData Defense;
	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldDefense) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Defense);
	
	//Strength
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Strength);
	
	//Agility
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Agility, Category = "Primary Attributes")
	FGameplayAttributeData Agility;
	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData& OldAgility) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Agility);
	
	//Penetration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Penetration, Category = "Primary Attributes")
	FGameplayAttributeData Penetration;
	UFUNCTION()
	void OnRep_Penetration(const FGameplayAttributeData& OldPenetration) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Penetration);
	
//
//Vital Attributes
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

	// Shield
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthFlask, Category = "Vital Attributes")
	FGameplayAttributeData HealthFlask;
	UFUNCTION()
	void OnRep_HealthFlask(const FGameplayAttributeData& OldHealthFlask) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, HealthFlask);
	
	// Armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Vital Attributes")
	FGameplayAttributeData Armor;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Armor);
	
	// Block Chance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Vital Attributes")
	FGameplayAttributeData BlockChance;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, BlockChance);
	
	// Stamina Recovery
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRecovery, Category = "Vital Attributes")
	FGameplayAttributeData StaminaRecovery;
	UFUNCTION()
	void OnRep_StaminaRecovery(const FGameplayAttributeData& OldStaminaRecovery) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, StaminaRecovery);

	// Physical Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamage, Category = "Vital Attributes")
	FGameplayAttributeData PhysicalDamage;
	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, PhysicalDamage);

	// Critical Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalDamage, Category = "Vital Attributes")
	FGameplayAttributeData CriticalDamage;
	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, CriticalDamage);

	// Attack Speed
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Vital Attributes")
	FGameplayAttributeData AttackSpeed;
	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, AttackSpeed);

	// Movement Speed
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Vital Attributes")
	FGameplayAttributeData MovementSpeed;
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MovementSpeed);

	// Crit Chance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritChance, Category = "Vital Attributes")
	FGameplayAttributeData CritChance;
	UFUNCTION()
	void OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, CritChance);

	// Stun Chance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StunChance, Category = "Vital Attributes")
	FGameplayAttributeData StunChance;
	UFUNCTION()
	void OnRep_StunChance(const FGameplayAttributeData& OldStunChance) const;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, StunChance);
	
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	
};
