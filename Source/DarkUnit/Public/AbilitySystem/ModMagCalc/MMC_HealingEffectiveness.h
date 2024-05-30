// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_HealingEffectiveness.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UMMC_HealingEffectiveness : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_HealingEffectiveness();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition StrengthDef;
};
