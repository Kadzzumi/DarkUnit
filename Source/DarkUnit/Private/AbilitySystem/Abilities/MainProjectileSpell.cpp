// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MainProjectileSpell.h"

#include "Actor/Projectile/ProjectileBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UMainProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	if (bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority(); !bIsServer) return;
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		FVector TargetLocation = ProjectileTargetLocation;
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatInterface->GetSpellSocketTransform().GetLocation());
		if (ProjectileTargetLocation.IsZero())
		{
			APlayerController* PC = Cast<APlayerController>(GetActorInfo().PlayerController);
			FVector CameraLocation;
			FRotator CameraRotation;

			// Get the player's viewpoint
			PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

			// Calculate the end point of the ray
			TargetLocation = CameraLocation + (CameraRotation.Vector() * 10000);
		}
		FRotator SpawnRotation = (TargetLocation - SpawnTransform.GetLocation()).Rotation();
		SpawnRotation.Pitch = 0.f;
		
		SpawnTransform.SetRotation(SpawnRotation.Quaternion());

		
		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileActor, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		// TODO: Apply spec for the projectile
		Projectile->FinishSpawning(SpawnTransform);
	}
	
}
