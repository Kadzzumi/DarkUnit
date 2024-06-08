// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_Evasion.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_Evasion::UMMC_Evasion()
{
	DexterityDef.AttributeToCapture = UMainAttributeSet::GetDexterityAttribute();
	DexterityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DexterityDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(DexterityDef);
}

float UMMC_Evasion::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Dexterity = 0.f;
	GetCapturedAttributeMagnitude(DexterityDef, Spec, EvaluateParameters, Dexterity);
	Dexterity = FMath::Max<float>(Dexterity, 0);

	return	10 + Dexterity;
}
