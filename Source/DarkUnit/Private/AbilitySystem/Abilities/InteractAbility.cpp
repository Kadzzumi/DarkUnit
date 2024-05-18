// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/InteractAbility.h"

#include <Kismet/KismetSystemLibrary.h>
#include "Character/Player/PlayerCharacterBase.h"

void UInteractAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;
	APlayerCharacterBase* PlayerCharacter = Cast<APlayerCharacterBase>(GetAvatarActorFromActorInfo());
	if (PlayerCharacter && PlayerCharacter->InteractingActorList.Num() > 0)
	{
		UKismetSystemLibrary::PrintString(this, FString("ActivateAbility Interact"), true, true, FLinearColor::Yellow, 3);
		if (AActor* ActorToDestroy = PlayerCharacter->InteractingActorList[0])
		{
			PlayerCharacter->InteractingActorList.Remove(ActorToDestroy);
			ActorToDestroy->Destroy();
			
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
