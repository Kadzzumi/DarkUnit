// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Evasion.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UMMC_Evasion : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_Evasion();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition DexterityDef;
};
