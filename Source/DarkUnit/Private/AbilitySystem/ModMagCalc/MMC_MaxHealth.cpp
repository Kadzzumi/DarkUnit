// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/MainAttributeSet.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/InteractionInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UMainAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0);
	float BaseVigorHealth{0.f};
	if (Vigor <= 30)
	{
		BaseVigorHealth = 20.f * Vigor;
	}
	else if (Vigor >= 31 && Vigor <= 50)
	{
		BaseVigorHealth =  90 + 17 * Vigor;
	}
	else if (Vigor >= 51 && Vigor <= 80)
	{
		BaseVigorHealth =  190 + 15 * Vigor;
	}
	else if (Vigor >= 81 && Vigor <= 100)
	{
		BaseVigorHealth =  430 + 12 * Vigor;
	}
	
	int32 PlayerLevel{1};
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}


	return 50.f + BaseVigorHealth + (PlayerLevel * 5); 
}
