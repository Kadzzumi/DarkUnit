// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacterBase.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AMainAIController;

/**
 * 
 */
UCLASS()
class DARKUNIT_API AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	AEnemyCharacterBase();

	virtual void PossessedBy(AController* NewController) override;
	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChange;

	
	// tag add or remove function
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 150.f;
	
	// Weapon
	virtual void SetAttackCollisions(const int32 Index) override;
	
	virtual void SetWeaponAttachment(AWeaponBase* Weapon) override;

	// Death
	virtual void Die() override;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(BlueprintReadOnly, Category = "Character Class Defaults", meta=(AllowPrivateAccess = "true"))
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta=(AllowPrivateAccess = "true"))
	ECharacterClass CharacterClass = ECharacterClass::Knight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	//AI Pops
	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> MainBehaviorTree;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<AMainAIController> MainAIController;
private:
	UPROPERTY(EditDefaultsOnly)
	float BonusDamage = 50;
	UPROPERTY(EditDefaultsOnly)
	float LifeSpanTime = 5.f;

};
