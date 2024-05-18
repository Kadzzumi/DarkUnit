// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DarkUnitInputConfig.h"
#include "EnhancedInputComponent.h"
#include "DarkUnitInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UDarkUnitInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const  UDarkUnitInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);	
};

//
// There are three functions that can be bound the input parameters
template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UDarkUnitInputComponent::BindAbilityActions(const UDarkUnitInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FDarkUnitInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{

			// It will be triggered only once when input is pressed 
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			// It will be triggered when the input is released
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			// Will be triggered every second as long as Input is pressed
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
