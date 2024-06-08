// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_CurseControl.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_CurseControl::UMMC_CurseControl()
{
	ResolveDef.AttributeToCapture = UMainAttributeSet::GetResolveAttribute();
	ResolveDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResolveDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ResolveDef);
}

float UMMC_CurseControl::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Resolve = 0.f;
	GetCapturedAttributeMagnitude(ResolveDef, Spec, EvaluateParameters, Resolve);
	Resolve = FMath::Max<float>(Resolve, 0);
	
	return	5 + Resolve;
}
