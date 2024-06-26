// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkUnitAssetManager.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystemGlobals.h"
UDarkUnitAssetManager& UDarkUnitAssetManager::Get()
{
	check(GEngine);
	UDarkUnitAssetManager* DarkUnitAssetManager = Cast<UDarkUnitAssetManager>(GEngine->AssetManager);
	return *DarkUnitAssetManager;
}

void UDarkUnitAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FDarkUnitGameplayTags::InitializeNativeGameplayTags();
	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
