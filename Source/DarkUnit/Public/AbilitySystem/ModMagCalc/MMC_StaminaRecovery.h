// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_StaminaRecovery.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UMMC_StaminaRecovery : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_StaminaRecovery();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition EnduranceDef;	
};
