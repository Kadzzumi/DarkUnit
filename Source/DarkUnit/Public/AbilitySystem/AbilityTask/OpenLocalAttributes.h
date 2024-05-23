// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "OpenLocalAttributes.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UOpenLocalAttributes : public UAbilityTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta= (DisplayName = "LocalAttributesMenu",HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UOpenLocalAttributes* OpenLocalAttributes(UGameplayAbility* OwningAbility);
private:
	virtual void Activate() override;
};
