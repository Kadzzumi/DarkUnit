#pragma once

#include "GameplayEffectTypes.h"
#include "DarkUnitAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDarkUnitGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	
	bool IsEvadedHit() const {return bIsEvadedHit; }

	void SetIsEvadedHit(bool bInIsEvadedHit) {bIsEvadedHit = bInIsEvadedHit; }

	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:

	UPROPERTY()
	bool bIsEvadedHit = false;
	
};
