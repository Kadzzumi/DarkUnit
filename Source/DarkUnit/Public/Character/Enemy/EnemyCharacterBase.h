// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacterBase.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class DARKUNIT_API AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	AEnemyCharacterBase();
	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChange;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta=(AllowPrivateAccess = "true"))
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta=(AllowPrivateAccess = "true"))
	ECharacterClass CharacterClass = ECharacterClass::Knight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
private:

};
