// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "ScalableFloat.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class UCapsuleComponent;
class UNiagaraSystem;



UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	State_Equipped UMETA(DisplayName = "Equipped"),
	State_Dropped UMETA(DisplayName = "Dropped"),
};

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UAnimMontage*> Montages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;
};

UCLASS()
class DARKUNIT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();
	virtual void Tick(float DeltaSeconds) override;

	void SetWeaponCollision(bool bCanHit);

	// Weapon Mesh
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;
	
	//Damage Effect SpecHandle
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UFUNCTION(Client, Reliable)
	void SetWeaponState(EWeaponState State);
	
	// Trace for combat
	UFUNCTION()
	void PerformTrace(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//
	// Weapon Level & Damage
	float GetWeaponDamage() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = 1, ClampMax = 10))
	int32 WeaponLevel;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeaponLevel(int32 NewWeaponLevel);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	FScalableFloat DamageCurve;

	UPROPERTY(EditDefaultsOnly, Category="Damage Types")
	FGameplayTag WeaponDamageTag;
	
	//
	UPROPERTY(EditAnywhere, Category="Damage Types")
	TArray<FTaggedMontage> AttackMontages;
	
protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, Category="Weapon")
	UCapsuleComponent* DamageCapsule;
	
	float TimeSinceLastTrace{0};
	bool bCanHitChar{false};  // Store the collision state
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

	// Weapon State
	UPROPERTY(VisibleAnywhere)
	EWeaponState WeaponState;
};
