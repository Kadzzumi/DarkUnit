
#include "AbilitySystem/Abilities/InteractAbility.h"

#include "Actor/Items/ItemBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Player/PlayerCharacterBase.h"


void UInteractAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
			if (AItemBase* Item = Cast<AItemBase>(ActorToDestroy))
			{
				PlayerCharacter->InteractingActorList.Remove(ActorToDestroy);
				Item->Interact(PlayerCharacter);
				ActorToDestroy->Destroy();
				//TODO::Interact with the ItemBase and get the StoredWeapon to the PlayerState WeaponInventory
			}

		}
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
