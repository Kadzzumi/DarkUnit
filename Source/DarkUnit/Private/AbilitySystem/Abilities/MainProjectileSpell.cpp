// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MainProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DarkUnitGameplayTags.h"
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
		FVector TargetLocation = CombatInterface->GetLookLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatInterface->GetSpellSocketTransform().GetLocation());

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
		const FDarkUnitGameplayTags GameplayTags = FDarkUnitGameplayTags::Get();
		for (auto& Pair : DamageTypes)
		{
			const float OverallDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, OverallDamage);
		}
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		// Spawn Finish
		Projectile->FinishSpawning(SpawnTransform);
	}
	
}
