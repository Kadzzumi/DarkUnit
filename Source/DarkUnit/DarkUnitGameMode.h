// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DarkUnitGameMode.generated.h"


class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class DARKUNIT_API ADarkUnitGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="CharacterClassInfo")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
