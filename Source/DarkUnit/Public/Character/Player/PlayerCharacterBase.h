// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/InteractionInterface.h"
#include "PlayerCharacterBase.generated.h"


class AMainPlayerState;
class UGameplayEffect;
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

   //Combat Interfaces
   virtual void AddToXP_Implementation(int32 InXP) override;
   virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
   virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
   
   virtual int32 GetXP_Implementation() const override;
   virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
   virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
   virtual void LevelUp_Implementation() override;
   virtual int32 GetPlayerLevel_Implementation() override;

   
   // Interact
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Items")
   TArray<AActor*> InteractingActorList;
   
   //Character Rotation
   UPROPERTY(EditAnywhere)
   bool bCanRotate = true;
   
   UFUNCTION(BlueprintCallable)
   virtual FVector GetLookLocation() override;
protected:
   
   virtual void BeginPlay() override;
   
   //Movement
   void SetRotation(bool bOrientToMovement, bool Yaw);
   void SetWeaponAttachments(AWeaponBase* Weapon, FName Socket) const;
   void SpawnWeapons(int32 Index);
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


};
