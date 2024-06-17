// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class AWeaponBase;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};


class DARKUNIT_API ICombatInterface
{
	GENERATED_BODY()

public:
	
	virtual int32 GetPlayerLevel();
	virtual void SetAttackCollisions(const int32 Index);
	virtual FTransform GetCombatSocketTransform();
	virtual FTransform GetSpellSocketTransform();
	virtual void SetWeaponAttachment(AWeaponBase* Weapon);
	virtual float CalculateOveralldDamage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();


	virtual void Die() = 0;
	
};
