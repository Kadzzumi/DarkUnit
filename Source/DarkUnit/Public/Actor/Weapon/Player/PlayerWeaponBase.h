// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/WeaponBase.h"
#include "PlayerWeaponBase.generated.h"


UENUM(BlueprintType)
enum class EWeaponDamageTier : uint8
{
	Tier_S UMETA(DisplayName = "S"),
	Tier_A UMETA(DisplayName = "A"),
	Tier_B UMETA(DisplayName = "B"),
	Tier_C UMETA(DisplayName = "C"),
	Tier_D UMETA(DisplayName = "D"),
	Tier_E UMETA(DisplayName = "E")
};

UCLASS()
class DARKUNIT_API APlayerWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
public:

	//Dmg
	//Weapon Damage Tier
	//
	float GetTierValue(EWeaponDamageTier DamageTier);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier StrengthDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier DexterityDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier IntelligenceDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier FaithDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier CurseDamageEff;
	
};
