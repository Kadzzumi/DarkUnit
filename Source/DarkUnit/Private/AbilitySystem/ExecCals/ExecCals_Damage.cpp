// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCals/ExecCals_Damage.h"

#include "AbilitySystemComponent.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/DarkUnitAbilitySystemLibrary.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct DarkUnitDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);

	// source
	DECLARE_ATTRIBUTE_CAPTUREDEF(Focus);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity);
	DarkUnitDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Defense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Evasion, Target, false);
		//Source
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Focus, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Strength, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Dexterity, Source, false);
	}
};

static const DarkUnitDamageStatics& DamageStatics()
{
	static DarkUnitDamageStatics DStatics;
	return DStatics;
}

UExecCals_Damage::UExecCals_Damage()
{
	//Target
	RelevantAttributesToCapture.Add(DamageStatics().DefenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().EvasionDef);
	
	//Source
	RelevantAttributesToCapture.Add(DamageStatics().FocusDef);
	RelevantAttributesToCapture.Add(DamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(DamageStatics().DexterityDef);

}

void UExecCals_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Getting Ability system component of the target and the character
	const UAbilitySystemComponent* SourceACS = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetACS = ExecutionParams.GetTargetAbilitySystemComponent();

	// Getting Avatars
	AActor* SourceAvatar = SourceACS ? SourceACS->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
		
	AActor* TargetAvatar = TargetACS ? TargetACS->GetAvatarActor() : nullptr;
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	
	// Gather tags from source and target
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;


	//Capture the Physical Defense
	

	// Target Attributes
	float TargetEvasionChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().EvasionDef, EvaluateParameters, TargetEvasionChance);
	TargetEvasionChance = FMath::Max(TargetEvasionChance, 0.f);

	float TargetDefense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefenseDef, EvaluateParameters, TargetDefense);
	TargetDefense = FMath::Max(TargetDefense, 0.f);

	// Source Attributes
	float SourceFocus = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FocusDef, EvaluateParameters, SourceFocus);
	SourceFocus = FMath::Max(SourceFocus, 0.f);
	
	float SourceStrength = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().StrengthDef, EvaluateParameters, SourceStrength);
	SourceStrength = FMath::Max(SourceStrength, 0.f);
	
	float SourceDexterity = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DexterityDef, EvaluateParameters, SourceDexterity);
	SourceDexterity = FMath::Max(SourceDexterity, 0.f);

	const UCharacterClassInfo* CharacterClassInfo = UDarkUnitAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* CharDamageCurve = CharacterClassInfo->CharacterDamageCurve->FindCurve(FName("CharDamagePerLevel"), FString());
	const float CharacterDamage = CharDamageCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	//
	//Calculation
	//Get DamageSet by collar mag/ Calculations
	float Damage = Spec.GetSetByCallerMagnitude(FDarkUnitGameplayTags::Get().Attributes_Damage_WeaponDamage);
	Damage += CharacterDamage;
	
	const bool bEvaded = FMath::RandRange(1, 100) < TargetEvasionChance/SourceFocus*10;
	Damage = bEvaded ? Damage / 2.f : Damage;
	
	const float PhysicalEffectiveDefense = 1-(TargetDefense/SourceStrength/SourceDexterity);
	
	Damage *= FMath::Clamp(PhysicalEffectiveDefense, 0.5f, 1);
	
	
	// Capture 
	const FGameplayModifierEvaluatedData EvaluatedData(UMainAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
