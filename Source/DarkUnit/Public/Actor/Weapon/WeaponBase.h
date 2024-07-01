// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "ScalableFloat.h"
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

	// Weapon Mesh
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;
	
	//Damage Effect SpecHandle
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;


	//Dmg
	//Weapon Damage Tier
	//
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

	UFUNCTION(Client, Reliable)
	void SetWeaponState(EWeaponState State);

	//
	// Weapon Level Damage
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
	float PhysicalDamage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = 1, ClampMax = 10))
	int32 WeaponLevel;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeaponLevel(int32 NewWeaponLevel);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	FScalableFloat DamageCurve;

protected:
	virtual void BeginPlay() override;
	// Trace for combat
	UFUNCTION()
	void PerformTrace();
	
	void SetupTraceParameters(FVector& Start, FVector& End, FVector& Direction, float& CapsuleHalfHeight, FQuat& CapsuleRotation) const;

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
