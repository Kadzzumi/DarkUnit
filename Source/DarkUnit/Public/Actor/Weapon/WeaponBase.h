// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class USphereComponent;
class UNiagaraSystem;

// Enum to represent the states of the actor
UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	InventoryState UMETA(DisplayName = "Inventory"),
	EquippedState UMETA(DisplayName = "Equipped"),
	InReserve UMETA(DisplayName = "InReserve")
};

UCLASS()
class DARKUNIT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	// Function to set the actor state
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetWeaponState(EWeaponState NewState);
	
	void SetWeaponCollision(bool bCanHit);
	
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void PerformTrace();
	// Add at the beginning of the private section
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayImpactEffects(const FVector& Location, const FRotator& Rotation);
private:
	UPROPERTY(VisibleAnywhere, Category="Weapon")
	USceneComponent* RootSceneComponent;
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;
	
	// The state of the actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	EWeaponState CurrentState;
	
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
};
