// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "GameplayEffectTypes.h"
#include "CharacterBase.generated.h"

struct FTaggedMontage;
class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class AWeaponBase;
class UAnimMontage;

UCLASS(Abstract)
class DARKUNIT_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess = "true"))
	AWeaponBase* PrimaryWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess = "true"))
	AWeaponBase* SecondaryWeapon;	
	
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	//Weapons
	virtual FTransform GetCombatSocketTransform() override;
	virtual FTransform GetSpellSocketTransform() override;
	virtual void SetWeaponAttachment(AWeaponBase* Weapon) override;
	UFUNCTION(BlueprintCallable)
	virtual void SetAttackCollisions(const bool bCanHit) override;
	// Damage Output
	virtual float CalculateOveralldDamage() override;

	//Death
	virtual void Die() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<FTaggedMontage> GetAttackMontages();
	
protected:
	virtual void BeginPlay() override;
	//Weapons
	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponSocketName = "RightHandSocket";
	
	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName = "WeaponTipSocket";
	
	//
	// GAS
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	void InitializeAttributes(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;
	void AddCharacterAbilities();

	// Death montage
	void PlayDeath() const;
		
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	UFUNCTION()
	void HandleDeath() const;

	//Dissolve Effects
	void Dissolve();
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> MI_CharacterDessolve;

	UFUNCTION(BlueprintCallable)
	void WeaponTrailEffect(bool bStart);

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;
	
	//Abilities
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//Passive abilities
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;


	
};
