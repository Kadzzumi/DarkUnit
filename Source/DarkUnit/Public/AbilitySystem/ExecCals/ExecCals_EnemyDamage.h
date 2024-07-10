// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCals_EnemyDamage.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UExecCals_EnemyDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCals_EnemyDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
