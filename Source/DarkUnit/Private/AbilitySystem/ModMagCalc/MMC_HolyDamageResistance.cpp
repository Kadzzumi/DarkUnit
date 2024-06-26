// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_HolyDamageResistance.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_HolyDamageResistance::UMMC_HolyDamageResistance()
{
	FaithDef.AttributeToCapture = UMainAttributeSet::GetFaithAttribute();
	FaithDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	FaithDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(FaithDef);
}

float UMMC_HolyDamageResistance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Faith = 0.f;
	GetCapturedAttributeMagnitude(FaithDef, Spec, EvaluateParameters, Faith);
	Faith = FMath::Max<float>(Faith, 0);

	return	10 + Faith;
}
