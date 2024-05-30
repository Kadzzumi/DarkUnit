// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacterBase.generated.h"


class UGameplayEffect;
/**
 * 
 */
UCLASS()
class DARKUNIT_API APlayerCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacterBase();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void PostInitializeComponents() override;
	//Tick
	virtual void Tick(float DeltaSeconds) override;

	//Movement
	float GetSpeed() const;

	//Combat Interface
	virtual int32 GetPlayerLevel() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Items")
	TArray<AActor*> InteractingActorList;

protected:
	
	virtual void BeginPlay() override;
	//Movement
	void SetRotation(bool bOrientToMovement, bool Yaw);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetAttackCollisions(const int32 Index) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
private:
	// Functions
	virtual void InitAbilityActorInfo() override;
	//Camera Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FRotator ZAxisRotation{FRotator(0.f, 540.f, 0.f)};
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UVitalComponent* VitalComponent;
	

	//
	//PickUp
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UCapsuleComponent* PickupSphere;
	
	// Function to handle the begin overlap event
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// Function to handle the end overlap event
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};




/*	// collisions for no weapon

	//Combat Collisions
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* LeftHandCollision;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* RightHandCollision;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* LeftLegCollision;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* RightLegCollision;

	UFUNCTION()
	void OnOverlapBeginLeftHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEndLeftHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapBeginRightHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEndRightHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapBeginLeftLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEndLeftLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapBeginRightLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEndRightLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
*/