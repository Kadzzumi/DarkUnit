// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/DataUnderCursor.h"

#include "AbilitySystemComponent.h"

UDataUnderCursor* UDataUnderCursor::CreateDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UDataUnderCursor* MyObj = NewAbilityTask<UDataUnderCursor>(OwningAbility);
	return MyObj;
}

void UDataUnderCursor::Activate()
{
    const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if (bIsLocallyControlled)
    {
        SendScreenData();
    }
    else
    {
        const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
        const FPredictionKey ActivatePredictionKey = GetActivationPredictionKey();
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivatePredictionKey).AddUObject(this, &UDataUnderCursor::OnTargetDataReplicatedCallback);
        const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivatePredictionKey);
        if (!bCalledDelegate)
        {
            SetWaitingOnRemotePlayerData();
        }
    }
}

void UDataUnderCursor::SendScreenData()
{
    FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
    APlayerController* PC = Cast<APlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get());
        FVector CameraLocation;
        FRotator CameraRotation;

        // Get the player's viewpoint
        PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

        // Calculate the end point of the ray
        FVector End = CameraLocation + (CameraRotation.Vector() * 10000);
        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(PC->GetPawn());
        
        GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, End, ECC_Visibility, CollisionParams);
        FGameplayAbilityTargetDataHandle DataHandle;
        FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
        Data->HitResult = HitResult;
        DataHandle.Add(Data);
        AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

        if (ShouldBroadcastAbilityTaskDelegates())
        {
            ValidData.Broadcast(DataHandle);
        }
}

void UDataUnderCursor::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
    FGameplayTag ActivationTag)
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(DataHandle);
    }
}


