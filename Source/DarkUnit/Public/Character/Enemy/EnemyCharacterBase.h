// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	AEnemyCharacterBase();
	
protected:
	virtual void BeginPlay() override;
};
