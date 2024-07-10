// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/Weapon/Player/PlayerWeaponBase.h"

float APlayerWeaponBase::GetTierValue(EWeaponDamageTier DamageTier)
{
	switch (DamageTier)
	{
	case EWeaponDamageTier::Tier_S:
		return 1.0f;
		break;
	case EWeaponDamageTier::Tier_A:
		return 0.8f;
		break;
	case EWeaponDamageTier::Tier_B:
		return 0.6f;
		break;
	case EWeaponDamageTier::Tier_C:
		return 0.4f;
		break;
	case EWeaponDamageTier::Tier_D:
		return 0.2f;
		break;
	case EWeaponDamageTier::Tier_E:
		return 0.f;
		break;
	}
	return 0;
}
