
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
void AMainPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

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


// 
void AMainPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(OldLevel);
}
void AMainPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AMainPlayerState::SetToLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

//Attribute Point
void AMainPlayerState::OnRep_AttributePoint(int32 OldAttributePoint)
{
	OnAttributePointChangedDelegate.Broadcast(OldAttributePoint);
}

void AMainPlayerState::AddToAttributePoint(int InAttributePoint)
{
	AttributePoint += InAttributePoint;
	OnAttributePointChangedDelegate.Broadcast(AttributePoint);
}

void AMainPlayerState::SetToAttributePoint(int InAttributePoint)
{
	AttributePoint = InAttributePoint;
	OnAttributePointChangedDelegate.Broadcast(AttributePoint);
}
