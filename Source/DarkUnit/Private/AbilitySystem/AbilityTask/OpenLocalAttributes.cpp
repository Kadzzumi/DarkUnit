// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/OpenLocalAttributes.h"

#include "PlayerController/MainPlayerController.h"

UOpenLocalAttributes* UOpenLocalAttributes::OpenLocalAttributes(UGameplayAbility* OwningAbility)
{
	UOpenLocalAttributes* MyObj = NewAbilityTask<UOpenLocalAttributes>(OwningAbility);
	return MyObj;
}

void UOpenLocalAttributes::Activate()
{
	Super::Activate();
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, TEXT("TaskActivated"));
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		AMainPlayerController* PC = Cast<AMainPlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get());
		if (UFunction* CustomEvent = PC->FindFunction(FName("OpenAttributeMenu")))
		{
			PC->ProcessEvent(CustomEvent, nullptr);
		}
	}
}
