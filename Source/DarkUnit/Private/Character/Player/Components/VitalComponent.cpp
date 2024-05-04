// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Components/VitalComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


UVitalComponent::UVitalComponent(): Player(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVitalComponent::BeginPlay()
{
	Super::BeginPlay();

	ApplyEffectToTheTarget();
	
}

void UVitalComponent::ApplyEffectToTheTarget()
{
	if (Player)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Player);
		if (TargetASC)
		{
			if (StaminaGameplayEffectClass)
			{
				// Get Target's AbilitySystemComponent
				FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
				EffectContextHandle.AddSourceObject(this);
				const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetASC->MakeOutgoingSpec(StaminaGameplayEffectClass, 1.0f, EffectContextHandle);
				const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
			}
		}
	}
}


void UVitalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UVitalComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

