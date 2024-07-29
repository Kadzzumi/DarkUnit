// Interface for the Level
#include "Interaction/CombatInterface.h"
#include "Actor/Weapon/WeaponBase.h"

void ICombatInterface::SetAttackCollisions(const bool bCanHit)
{
	
}

FVector ICombatInterface::GetLookLocation()
{
	return FVector();
}

FTransform ICombatInterface::GetCombatSocketTransform()
{
	return FTransform();
}

FTransform ICombatInterface::GetSpellSocketTransform()
{
	return FTransform();
}

void ICombatInterface::SetWeaponAttachment(AWeaponBase* Weapon)
{
	
}

float ICombatInterface::CalculateOveralldDamage()
{
	return 0;
}
