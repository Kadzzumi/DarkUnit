// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_StatusEffecResistance.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UMMC_StatusEffecResistance : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_StatusEffecResistance();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition StrengthDef;
};
