// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/InteractionInterface.h"
#include "PlayerCharacterBase.generated.h"


class APlayerWeaponBase;
class AMainPlayerState;
class UGameplayEffect;
class UParticleSystemComponent;
class USoundCue;
/**
 * 
 */
UCLASS()
class DARKUNIT_API APlayerCharacterBase : public ACharacterBase, public IInteractionInterface
{
   GENERATED_BODY()
public:
   APlayerCharacterBase();
   virtual void PossessedBy(AController* NewController) override;
   virtual void OnRep_PlayerState() override;
   
   //Tick
   virtual void Tick(float DeltaSeconds) override;

   //Movement
   float GetSpeed() const;

   // Combat
   UFUNCTION(BlueprintCallable)
   void SwapWeapons();
   UFUNCTION(BlueprintCallable)
   void SetRotationMode(AActor* Target);
   FRotator LockOnEnemy() const;
   
   //Combat Interfaces
   //Attribute
   virtual void AddToXP_Implementation(int32 InXP) override;
   virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
   virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
   virtual int32 GetAttributePoint_Implementation() const override;

   //XP and Level
   virtual int32 GetXP_Implementation() const override;
   virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
   virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
   virtual void LevelUp_Implementation() override;
   virtual int32 GetPlayerLevel_Implementation() override;


   // Interact
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Items")
   TArray<AActor*> InteractingActorList;
   
   //Character Rotation
   UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
   bool bOrientToTheMovement = true;
   
   UFUNCTION(BlueprintCallable)
   virtual FVector GetLookLocation() override;

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
   TObjectPtr<UParticleSystemComponent> LevelUpParticle;

   UPROPERTY(EditAnywhere, BlueprintReadOnly)
   USoundCue* LevelUpSound;

   UPROPERTY(EditAnywhere, BlueprintReadWrite)
   int32 LightCombo{0};
protected:
   
   virtual void BeginPlay() override;
   
   //Movement
   void UpdateWeaponAbilities(const AWeaponBase* Weapon) const;
   void SetWeaponAttachments(AWeaponBase* Weapon, FName Socket) const;
   void SpawnWeapons(int32 Index);

   
private:
   // Functions
   virtual void InitAbilityActorInfo() override;

   UFUNCTION(NetMulticast, Reliable)
   void MulticastLevelUpCues() const;
   //Camera Components
   UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
   class USpringArmComponent* SpringArm;

   UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
   class UCameraComponent* Camera;

   UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
   FRotator ZAxisRotation{FRotator(0.f, 540.f, 0.f)};
   
   //
   //PickUp
   UPROPERTY(EditDefaultsOnly, Category="PickUp")
   UCapsuleComponent* PickupSphere;
   
   // Function to handle the begin overlap event
   UFUNCTION()
   void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
   
   // Function to handle the end overlap event
   UFUNCTION()
   void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

   AActor* LockTarget{nullptr};
   UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
   float LockRotationRate{5.f};
};
