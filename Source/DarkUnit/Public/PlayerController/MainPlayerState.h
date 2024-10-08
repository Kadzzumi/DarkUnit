// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

class ULevelUpInfo;
class APlayerWeaponBase;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*Stat Value*/)

UCLASS()
class DARKUNIT_API AMainPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AMainPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet; }

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

	//
	// Getter and setter
	// Level Getter
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	void AddToLevel(int32 InLevel);
	void SetToLevel(int32 InLevel);
	FOnPlayerStatChanged OnLevelChangedDelegate;
	
	//XP Sets
	FORCEINLINE int32 GetXP() const { return XP; }
	void AddToXP(int InXP);
	void SetToXP(int InXP);
	FOnPlayerStatChanged OnXPChangedDelegate;

	//AttributePoint Sets
	FORCEINLINE int32 GetAttributePoint() const { return AttributePoint; }
	void AddToAttributePoint(int InAttributePoint);
	void SetToAttributePoint(int InAttributePoint);
	FOnPlayerStatChanged OnAttributePointChangedDelegate;

	//
	//Inventory
	const int32 MaxWeaponCapacity{ 2 };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<APlayerWeaponBase>> WeaponInventory;

	UPROPERTY(VisibleAnywhere)
	APlayerWeaponBase* EquippedWeapon1{nullptr};
	
	UPROPERTY(VisibleAnywhere)
	APlayerWeaponBase* EquippedWeapon2{nullptr};
	

	
	
protected:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	
private:
	//Attributes
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 1;
	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoint)
	int32 AttributePoint = 0;
	UFUNCTION()
	void OnRep_AttributePoint(int32 OldAttributePoint);
};
