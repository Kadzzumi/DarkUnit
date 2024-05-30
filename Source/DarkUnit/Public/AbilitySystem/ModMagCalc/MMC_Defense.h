// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Defense.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UMMC_Defense : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_Defense();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition StrengthDef;
};
