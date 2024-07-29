// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
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
	UFUNCTION(BlueprintNativeEvent)
	int32 GetPlayerLevel();
	virtual void SetAttackCollisions(const bool bCanHit);
	//
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GetTargetLocation();
	virtual FVector GetLookLocation();
	//Spell Sockets;
	virtual FTransform GetCombatSocketTransform();
	virtual FTransform GetSpellSocketTransform();
	//Weapon
	virtual void SetWeaponAttachment(AWeaponBase* Weapon);
	virtual float CalculateOveralldDamage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();


	virtual void Die() = 0;

	//TODO:Have to figure out how to get the montages from the weapon and set them in the right manner
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ECharacterClass GetCharacterClass();
};
