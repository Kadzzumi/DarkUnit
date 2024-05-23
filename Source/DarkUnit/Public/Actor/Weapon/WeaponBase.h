// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <NiagaraSystem.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class USphereComponent;
class UNiagraSystem;

// Enum to represent the states of the actor
UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	PickedUpState UMETA(DisplayName = "Picked Up"),
	EquippedState UMETA(DisplayName = "Equipped"),
	WorldState UMETA(DisplayName = "In World")
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
	
	void SetWeaponCollision(bool bCanHit) const;
protected:
	virtual void BeginPlay() override;

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	UPROPERTY(VisibleAnywhere, Category="Weapon")
	USceneComponent* RootSceneComponent;
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	UBoxComponent* WeaponCollision;
	// The state of the actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	EWeaponState CurrentState;
	
	//Cues
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ImpactEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
};
