// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DarkUnitAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API UDarkUnitAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UDarkUnitAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
	

};
