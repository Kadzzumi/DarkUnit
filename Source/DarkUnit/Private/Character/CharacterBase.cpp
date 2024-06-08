// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Actor/Weapon/WeaponBase.h"


ACharacterBase::ACharacterBase(): PrimaryWeapon(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FTransform ACharacterBase::GetCombatSocketTransform()
{
	return GetMesh()->GetSocketTransform(WeaponSocketName);
}

void ACharacterBase::SetWeaponAttachment(AWeaponBase* Weapon)
{

}


void ACharacterBase::InitAbilityActorInfo()
{
	
}

void ACharacterBase::InitializeAttributes(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ACharacterBase::InitializeDefaultAttributes() const
{
	InitializeAttributes(DefaultPrimaryAttributes, 1.f);
	InitializeAttributes(DefaultSecondaryAttributes, 1.f);
	InitializeAttributes(DefaultVitalAttributes, 1.f);
	
}

void ACharacterBase::AddCharacterAbilities()
{
	UMainAbilitySystemComponent* DarkUnitASC = Cast<UMainAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
	
	DarkUnitASC->AddCharacterAbilities(StartupAbilities);
	
}

float ACharacterBase::CalculateOveralldDamage()
{
	return ICombatInterface::CalculateOveralldDamage();
}

UAnimMontage* ACharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}


