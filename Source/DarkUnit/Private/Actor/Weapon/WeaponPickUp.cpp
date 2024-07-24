// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponPickUp.h"
#include "Actor/Weapon/Player/PlayerWeaponBase.h"
#include "Character/Player/PlayerCharacterBase.h"
#include "PlayerController/MainPlayerState.h"

void AWeaponPickUp::Interact(APlayerCharacterBase* Player)
{
	if (StoredWeapon)
	{
		AMainPlayerState* MainPlayerState = Cast<AMainPlayerState>(Player->GetPlayerState());
		MainPlayerState->WeaponInventory.Add(StoredWeapon);
	}

	Destroy();
}
