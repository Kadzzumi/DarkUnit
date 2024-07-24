// Fill out your copyright notice in the Description page of Project Settings.
#include "AbilitySystem/DarkUnitAbilitySystemLibrary.h"

#include "AttributeSet.h"
#include "DarkUnitAbilityTypes.h"
#include "AbilitySystem/Abilities/DarkUnitGameplayAbility.h"
#include "DarkUnit/DarkUnitGameMode.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/MainPlayerState.h"
#include "UI/HUD/MainHUD.h"
#include "UI/WidgetController/MainWidgetController.h"


UOverlayWidgetController* UDarkUnitAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMainHUD* MainHUD = Cast<AMainHUD>(PC->GetHUD()))
		{
			AMainPlayerState* PS = PC->GetPlayerState<AMainPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return MainHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeWidgetController* UDarkUnitAbilitySystemLibrary::GetAttributeWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMainHUD* MainHUD = Cast<AMainHUD>(PC->GetHUD()))
		{
			AMainPlayerState* PS = PC->GetPlayerState<AMainPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return MainHUD->GetAttributeWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UDarkUnitAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo =  GetCharacterClassInfo(WorldContextObject);
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.AIPrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UDarkUnitAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo =  GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
	for (const TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.AIStartUpAbilities)
	{
		//TODO:Get Enemy Level
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
		ASC->GiveAbility(AbilitySpec);
	}
}
//XP reward
int32 UDarkUnitAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo* CharacterClassInfo =  GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return 0;
	const FCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);
	return static_cast<int32>(XPReward);
}

UCharacterClassInfo* UDarkUnitAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ADarkUnitGameMode* MainGameMode = Cast<ADarkUnitGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MainGameMode == nullptr) return nullptr;
	
	return MainGameMode->CharacterClassInfo;

}

bool UDarkUnitAbilitySystemLibrary::IsEvadedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDarkUnitGameplayEffectContext* DarkUnitEffectContext = static_cast<const FDarkUnitGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return DarkUnitEffectContext->IsEvadedHit();
	}
	return false;
	
}

void UDarkUnitAbilitySystemLibrary::SetIsEvadedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsEvaded)
{
	if (FDarkUnitGameplayEffectContext* DarkUnitEffectContext = static_cast<FDarkUnitGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		DarkUnitEffectContext->SetIsEvadedHit(bInIsEvaded);
	}
}


