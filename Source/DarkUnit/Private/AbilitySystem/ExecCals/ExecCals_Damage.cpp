// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCals/ExecCals_Damage.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/DarkUnitAbilitySystemLibrary.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct DarkUnitDamageStatics
{
	//Target
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicDefense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireDamageResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningDamageResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IceDamageResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HolyDamageResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurseResistance);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);

	// source
	DECLARE_ATTRIBUTE_CAPTUREDEF(Focus);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity);

	//TMap to capture defs for defense
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	DarkUnitDamageStatics()
	{
		//Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Defense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, MagicDefense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, FireDamageResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, LightningDamageResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, IceDamageResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, HolyDamageResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, CurseResistance, Target, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Evasion, Target, false);
		//Source
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Focus, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Strength, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Dexterity, Source, false);

		const FDarkUnitGameplayTags& Tags = FDarkUnitGameplayTags::Get();

		//Offenses
		// TagsToCaptureDefs.Add(Tags.Attributes_Damage_Curse, CurseResistanceDef);



		//Defenses
		TagsToCaptureDefs.Add(Tags.Attributes_Resistances_Defense, DefenseDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistances_MagicDefense, MagicDefenseDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistances_FireResistance, FireDamageResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistances_IceResistance, IceDamageResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistances_LightningResistance, LightningDamageResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistances_HolyDamageResistance, HolyDamageResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistances_CurseResistance, CurseResistanceDef);
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
	RelevantAttributesToCapture.Add(DamageStatics().MagicDefenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().IceDamageResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireDamageResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningDamageResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().HolyDamageResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CurseResistanceDef);
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
	float Damage{CharacterDamage};
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FDarkUnitGameplayTags::Get().DamageTypesToResistances)
	{
		// const FGameplayTag DamageTag = Pair.Key;
		const FGameplayTag DefenseTag = Pair.Value;
		
		checkf(DarkUnitDamageStatics().TagsToCaptureDefs.Contains(DefenseTag), TEXT("Tags to capture defs doesnot contain Tag: [%s] in the execcals_Damage"), *DefenseTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = DarkUnitDamageStatics().TagsToCaptureDefs[DefenseTag];
		
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false, 0.f);
		float DefenseType{0};
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParameters, DefenseType);
		
		if (DamageTypeValue > 0.f && DefenseType > 0.f)
		{
			const float EffectiveDefense = 1-(DefenseType/DamageTypeValue/2);
			UE_LOG(LogTemp, Warning, TEXT("Damage : %f"), DamageTypeValue);
			UE_LOG(LogTemp, Warning, TEXT("Defence : %f"), EffectiveDefense);
			DamageTypeValue *= FMath::Clamp(EffectiveDefense, 0.5f, 1);
		}
		Damage += DamageTypeValue;
		UE_LOG(LogTemp, Warning, TEXT("Damage : %f"), Damage);
	}
	
	const bool bEvaded = FMath::RandRange(1, 100) < TargetEvasionChance/SourceFocus*10;
	// Getting Context 
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UDarkUnitAbilitySystemLibrary::SetIsEvadedHit(EffectContextHandle, bEvaded);
	
	Damage = bEvaded ? Damage / 2.f : Damage;
	
	// Capture 
	const FGameplayModifierEvaluatedData EvaluatedData(UMainAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}