// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"


ACharacterBase::ACharacterBase(): PrimaryWeapon(nullptr), DeathMontage(nullptr)
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
	if(Weapon == nullptr) return;
	if (const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(WeaponSocketName))
	{
		// Attach the Weapon to the hand socket RightHandSocket
		PrimaryWeapon = Weapon;
		HandSocket->AttachActor(PrimaryWeapon, GetMesh());
	}
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

//
//Hit react and Death
UAnimMontage* ACharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ACharacterBase::Die()
{
	if (PrimaryWeapon != nullptr)
	{
		PrimaryWeapon->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		PrimaryWeapon->SetLifeSpan(7.f);
	}
	MulticastHandleDeath();
}

void ACharacterBase::MulticastHandleDeath_Implementation()
{
	if (PrimaryWeapon != nullptr)
	{
		PrimaryWeapon->SetWeaponState(EWeaponState::State_Dropped);
	}
	HandleDeath();
	PlayDeath();
	Dissolve();
}
void ACharacterBase::PlayDeath() const
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage, 1.0f);
	}
}

void ACharacterBase::HandleDeath() const
{
	// Disable all collisions
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Component : Components)
	{
		if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component))
		{
			PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ACharacterBase::Dissolve()
{
	if(IsValid(MI_CharacterDessolve))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(MI_CharacterDessolve, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
}


