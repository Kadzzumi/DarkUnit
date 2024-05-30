// Interface for the Level
#include "Interaction/CombatInterface.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Engine/SkeletalMeshSocket.h"

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

void ICombatInterface::SetWeaponAttachment(AWeaponBase* Weapon)
{
	
}
