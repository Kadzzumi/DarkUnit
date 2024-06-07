
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
	DOREPLIFETIME(AMainPlayerState, Level);
	DOREPLIFETIME(AMainPlayerState, PrimaryWeapon);
}

void AMainPlayerState::OnRep_Level(int32 OldLevel)
{
	
}

void AMainPlayerState::OnRep_PrimaryWeapon()
{
	
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMainPlayerState::UpdateWeaponInventory(AWeaponBase* Weapon, bool bIsAdding)
{
	if (bIsAdding)
	{
		if (WeaponInventory.Num() >= 0)
		{
			PrimaryWeapon = Weapon;
		}
		WeaponInventory.Add(Weapon);
	}
	else
	{
		WeaponInventory.Remove(Weapon);
	}
}
