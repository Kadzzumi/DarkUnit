// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AbilityInfo.h"

#include "DarkUnit/DarkUnitLogChannels.h"

FDarkUnitAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FDarkUnitAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogDarkUnit, Error, TEXT("Can't find info for hte tag [%s] on abilityinfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	return FDarkUnitAbilityInfo();
}
