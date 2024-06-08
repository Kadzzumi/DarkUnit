// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

class AWeaponBase;
class UAbilitySystemComponent;
class UAttributeSet;

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
	// Level Getter
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE AWeaponBase* GetPrimaryWeapon() const {return PrimaryWeapon; }

	void UpdateWeaponInventory(AWeaponBase* Weapon, bool bIsAdding);
	
protected:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:
		
	UPROPERTY(EditAnywhere)
	TArray<AWeaponBase*> WeaponInventory;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_PrimaryWeapon)
	AWeaponBase* PrimaryWeapon;
	UFUNCTION()
	void OnRep_PrimaryWeapon();
};
