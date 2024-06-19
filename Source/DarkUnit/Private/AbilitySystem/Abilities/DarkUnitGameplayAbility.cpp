 // Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DarkUnitGameplayAbility.h"

#include "Interaction/CombatInterface.h"

 void UDarkUnitGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
  bool bReplicateEndAbility, bool bWasCancelled)
 {
  Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
  SetCollisions(0);
 }

 void UDarkUnitGameplayAbility::SetCollisions(int32 Index)
 {
  const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
  if (!bIsServer) return;
  // 0 is no collision/ can't do damage
  // 1 is left hand collision on
  // 2 is right hand collision on
  // 3 is left leg collision on
  // 4 is right leg collision on
		
  if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
  {
   CombatInterface->SetAttackCollisions(Index);
  }
 }
