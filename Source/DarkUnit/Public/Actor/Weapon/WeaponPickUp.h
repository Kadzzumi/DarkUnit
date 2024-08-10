// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Items/ItemBase.h"
#include "WeaponPickUp.generated.h"

class UGameplayEffect;
class APlayerWeaponBase;
/**
 * 
 */
UCLASS()
class DARKUNIT_API AWeaponPickUp : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void Interact(APlayerCharacterBase* Player) override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerWeaponBase> StoredWeapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
};
