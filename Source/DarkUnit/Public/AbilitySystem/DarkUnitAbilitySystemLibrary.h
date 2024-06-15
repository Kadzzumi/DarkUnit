// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "DarkUnitAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class UAttributeWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class DARKUNIT_API UDarkUnitAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "DarkUnitAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "DarkUnitAbilitySystemLibrary|WidgetController")
	static UAttributeWidgetController* GetAttributeWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="DarkUnitAbilitySystemLibrary|CharacterClassInfo")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="DarkUnitAbilitySystemLibrary|CharacterClassInfo")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject); 
};
