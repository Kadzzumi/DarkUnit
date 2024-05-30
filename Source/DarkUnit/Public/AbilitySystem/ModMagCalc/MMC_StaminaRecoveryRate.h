// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_StaminaRecoveryRate.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UMMC_StaminaRecoveryRate : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_StaminaRecoveryRate();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition StrengthDef;
};
