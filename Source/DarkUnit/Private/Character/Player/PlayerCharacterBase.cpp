// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/EnemyCharacterBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/MainPlayerController.h"
#include "PlayerController/MainPlayerState.h"
#include "UI/HUD/MainHUD.h"

APlayerCharacterBase::APlayerCharacterBase()
{
   PrimaryActorTick.bCanEverTick = true;
   // Create Spring Arm Component
   SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
   SpringArm->SetupAttachment(RootComponent);
   SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 50.f)); // Adjust as needed
   SpringArm->TargetArmLength = 350.f; // Adjust as needed
   SpringArm->bUsePawnControlRotation = true;

   // Create Camera Component
   Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
   Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

   // SetupCharacter Movement 
   SetRotation(false, true);
   GetCharacterMovement()->RotationRate = ZAxisRotation;
   bUseControllerRotationPitch = false;
   bUseControllerRotationRoll = false;
   
   //
   //Pickup
   // Bind the overlap events
   // Set up collision responses
   PickupSphere = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereComponent"));
   PickupSphere->SetupAttachment(GetRootComponent());
   PickupSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
   PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::OnSphereBeginOverlap);
   PickupSphere->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnSphereEndOverlap);
   PickupSphere->SetGenerateOverlapEvents(true);
}

// Init Ability Actor Info
void APlayerCharacterBase::PossessedBy(AController* NewController)
{
   Super::PossessedBy(NewController);
   InitAbilityActorInfo();
   AddCharacterAbilities();
}
void APlayerCharacterBase::OnRep_PlayerState()
{
   Super::OnRep_PlayerState();
   InitAbilityActorInfo();
   
}

//
//BeginPlay and Tick
//
void APlayerCharacterBase::BeginPlay()
{
   Super::BeginPlay();
   //Weapon Equip

}

void APlayerCharacterBase::Tick(float DeltaSeconds)
{
   Super::Tick(DeltaSeconds);
   // Orient Rotation
   const UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
   if (AnimInstance == nullptr) return;
   if (GetSpeed() <= 0.f || AnimInstance->IsAnyMontagePlaying())
   {
      SetRotation(true, false);
   }
   else
   {
      SetRotation(false, true);
   }
   
}

void APlayerCharacterBase::InitAbilityActorInfo()
{
   //Init Ability Actor Info For the Server
   AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   MainPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MainPlayerState, this);
   Cast<UMainAbilitySystemComponent>(MainPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
   AbilitySystemComponent = MainPlayerState->GetAbilitySystemComponent();
   AttributeSet = MainPlayerState->GetAttributeSet();
   
   if (AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController()))
   {
      if (AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD()))
      {
         MainHUD->InitOverlay(PlayerController, MainPlayerState, AbilitySystemComponent, AttributeSet);
      }
   }
   InitializeDefaultAttributes();
}

void APlayerCharacterBase::SetRotation(bool bOrientToMovement, bool Yaw)
{
   GetCharacterMovement()->bOrientRotationToMovement = bOrientToMovement;
   bUseControllerRotationYaw = Yaw;
   
}


//Speed
float APlayerCharacterBase::GetSpeed() const
{
   FVector Velocity{GetVelocity()};
   Velocity.Z = 0.f;
   return Velocity.Size();
}
//
//Player Level
int32 APlayerCharacterBase::GetPlayerLevel()
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);

   return MainPlayerState->GetPlayerLevel();
}


//
//Pickup
//
void APlayerCharacterBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   InteractingActorList.AddUnique(OtherActor);
   if (AWeaponBase* Item = Cast<AWeaponBase>(OtherActor))
   {
      InteractingActorList.AddUnique(Item);
   }
}

void APlayerCharacterBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
   InteractingActorList.Remove(OtherActor);
   if (AWeaponBase* Item = Cast<AWeaponBase>(OtherActor))
   {
      InteractingActorList.Remove(Item);
   }
}
FVector APlayerCharacterBase::GetLookLocation()
{
   if (AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController()))
   {
      const APlayerController* PC = Cast<APlayerController>(PlayerController);
      FVector CameraLocation;
      FRotator CameraRotation;

      // Get the player's viewpoint
      PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

      // Calculate the end point of the ray
      return CameraLocation + (CameraRotation.Vector() * 10000);
   }
   return FVector();;
}

// Weapon
AWeaponBase* APlayerCharacterBase::GetMainWeapon()
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   if (PrimaryWeapon == nullptr)
   {
       return MainPlayerState->WeaponInventory[0];
   }
   else
   {
      return MainPlayerState->WeaponInventory[1];
   }
}

void APlayerCharacterBase::SetWeaponAttachment(AWeaponBase* Weapon)
{
   if(Weapon == nullptr) return;
   // Get the Hand Socket
   if (const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(WeaponSocketName))
   {
      // Attach the Weapon to the hand socket RightHandSocket
      if (PrimaryWeapon == nullptr)
      {
         PrimaryWeapon = Weapon;
         PrimaryWeapon->SetWeaponState_Implementation(EWeaponState::State_Equipped);
         HandSocket->AttachActor(PrimaryWeapon, GetMesh());  
      }
      else
      {
         SecondaryWeapon = Weapon;
         SecondaryWeapon->SetWeaponState_Implementation(EWeaponState::State_Equipped);
         HandSocket->AttachActor(SecondaryWeapon, GetMesh());
         PrimaryWeapon->Destroy();
      }
   }
}


