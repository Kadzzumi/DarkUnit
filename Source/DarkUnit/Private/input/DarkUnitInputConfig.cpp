// Fill out your copyright notice in the Description page of Project Settings.


#include "input/DarkUnitInputConfig.h"

const UInputAction* UDarkUnitInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
	for (const FDarkUnitInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
		
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant find  the tag for the input action: %s"), *InputTag.ToString());
	}
	return nullptr;
}
