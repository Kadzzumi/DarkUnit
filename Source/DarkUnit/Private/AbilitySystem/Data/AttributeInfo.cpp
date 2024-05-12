// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FDarkUnitAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag,
	const bool bLogNotFound)
{
	for (const FDarkUnitAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			if (Info.AttributeTag.MatchesTagExact(AttributeTag))
			{
				return Info;
			}
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant find info for the attribute tag [%s] on the attribute info [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FDarkUnitAttributeInfo();
}
