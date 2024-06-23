// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MainProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/Projectile/ProjectileBase.h"
#include "Interaction/CombatInterface.h"


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
		const FRotator SpawnRotation = (TargetLocation - SpawnTransform.GetLocation()).Rotation();
		SpawnTransform.SetRotation(SpawnRotation.Quaternion());

		
		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileActor, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		// Effect Context Handle
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		EffectContextHandle.AddHitResult(HitResult);
		HitResult.Location = ProjectileTargetLocation; 
		
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		// Spawn Finish
		Projectile->FinishSpawning(SpawnTransform);
	}
	
}
