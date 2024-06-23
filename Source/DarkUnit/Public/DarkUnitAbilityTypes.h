#pragma once

#include "GameplayEffectTypes.h"
#include "DarkUnitAbilityTypes.generated.h"



USTRUCT(BlueprintType)
struct FDarkUnitGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	// ReSharper disable once CppAccessSpecifierWithNoDeclarations
private:
	
public:
	
	bool IsEvadedHit() const {return bIsEvadedHit; }

	void SetIsEvadedHit(bool bInIsEvadedHit) {bIsEvadedHit = bInIsEvadedHit; }

	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FDarkUnitGameplayEffectContext* Duplicate() const
	{
		FDarkUnitGameplayEffectContext* NewContext = new FDarkUnitGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
protected:

	UPROPERTY()
	bool bIsEvadedHit = false;

	
};

template<>
struct TStructOpsTypeTraits<FDarkUnitGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FDarkUnitGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		
		WithCopy = true
	};
};
