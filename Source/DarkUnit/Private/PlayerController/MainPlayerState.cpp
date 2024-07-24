
#include "PlayerController/MainPlayerState.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Net/UnrealNetwork.h"

AMainPlayerState::AMainPlayerState() 
{
	//GAS
	AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UMainAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AMainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//Replicated Attributes
	DOREPLIFETIME(AMainPlayerState, Level);
	DOREPLIFETIME(AMainPlayerState, XP);


}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}



//XP setters/Getters Replicated
void AMainPlayerState::AddToXP(int InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AMainPlayerState::SetToXP(int InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}
void AMainPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

// 
void AMainPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(OldLevel);
}
void AMainPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(InLevel);
}

void AMainPlayerState::SetToLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(InLevel);
}
