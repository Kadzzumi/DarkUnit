// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class USphereComponent;
class UNiagaraSystem;

UENUM(BlueprintType)
enum class EWeaponDamageTier : uint8
{
	Tier_S UMETA(DisplayName = "S"),
	Tier_A UMETA(DisplayName = "A"),
	Tier_B UMETA(DisplayName = "B"),
	Tier_C UMETA(DisplayName = "C"),
	Tier_D UMETA(DisplayName = "D"),
	Tier_E UMETA(DisplayName = "E")
};

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	State_Equipped UMETA(DisplayName = "Equipped"),
	State_Dropped UMETA(DisplayName = "Dropped"),
};

UCLASS()
class DARKUNIT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	void SetWeaponCollision(bool bCanHit);

	//Damage Effect SpecHandle
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;


	//Dmg
	//Weapon Damage Tier
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float PhysicalDamage = 50.f;
	
	float GetTierValue(EWeaponDamageTier DamageTier);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	float StrengthCoff;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier StrengthDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier DexterityDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier IntelligenceDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier FaithDamageEff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EWeaponDamageTier CurseDamageEff;

	void SetWeaponState(EWeaponState State);
protected:
	virtual void BeginPlay() override;
	// Trace for combat
	UFUNCTION()
	void PerformTrace();
	// Add at the beginning of the private section
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayImpactEffects(const FVector& Location, const FRotator& Rotation);

	// WeaponDissolve
	void Dissolve();
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> MI_WeaponDessolve;
private:
	// Root and mesh
	UPROPERTY(VisibleAnywhere, Category="Weapon")
	USceneComponent* RootSceneComponent;
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;
	
	//Cues
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ImpactEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	//CollisionTrace
	UPROPERTY(EditAnywhere)
	TSet<AActor*> HitActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee", meta = (AllowPrivateAccess = "true"))
	float CapsuleRadius;
	
	FTimerHandle AttackTimerHandle;

	// Weapon State
	UPROPERTY(VisibleAnywhere)
	EWeaponState WeaponState;
};
