// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_Evasion.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_Evasion::UMMC_Evasion()
{
	StrengthDef.AttributeToCapture = UMainAttributeSet::GetStrengthAttribute();
	StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StrengthDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(StrengthDef);
}

float UMMC_Evasion::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Strength = 0.f;
	GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluateParameters, Strength);
	Strength = FMath::Max<float>(Strength, 0);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return	10 + Strength + PlayerLevel/2;
}
