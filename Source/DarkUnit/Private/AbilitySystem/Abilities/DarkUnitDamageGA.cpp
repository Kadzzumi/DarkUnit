// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DarkUnitDamageGA.h"

#include "Interaction/CombatInterface.h"

void UDarkUnitDamageGA::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	SetCollisions(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDarkUnitDamageGA::SetCollisions(bool bCanHit)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
		
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		CombatInterface->SetAttackCollisions(bCanHit);
	}
}
