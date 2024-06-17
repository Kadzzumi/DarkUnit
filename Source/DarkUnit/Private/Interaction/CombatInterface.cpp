// Interface for the Level
#include "Interaction/CombatInterface.h"


int32 ICombatInterface::GetPlayerLevel()
{
	return 0;
}

void ICombatInterface::SetAttackCollisions(const int32 Index)
{
	
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
