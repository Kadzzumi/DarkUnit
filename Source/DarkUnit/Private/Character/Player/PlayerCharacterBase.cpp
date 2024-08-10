// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Actor/Weapon/Player/PlayerWeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/EnemyCharacterBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerController/MainPlayerController.h"
#include "PlayerController/MainPlayerState.h"
#include "Sound/SoundCue.h"
#include "UI/HUD/MainHUD.h"

APlayerCharacterBase::APlayerCharacterBase()
{
   LevelUpParticle = CreateDefaultSubobject<UParticleSystemComponent>("LevelUpParticle");
   LevelUpParticle->SetupAttachment(GetRootComponent());
   LevelUpParticle->bAutoActivate = false;
   
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
   //Weapon Equip
   SpawnWeapons(0);
   SpawnWeapons(1);
   InitAbilityActorInfo();
   AddCharacterAbilities();
   UpdateWeaponAbilities(PrimaryWeapon);
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
   SetRotationMode(nullptr);
}


void APlayerCharacterBase::Tick(float DeltaSeconds)
{
   Super::Tick(DeltaSeconds);
   // Orient Rotation
   if (GetSpeed() >= 500.f)
   {
      SetRotationMode(nullptr);
   }
   else
   {
      if (!bOrientToTheMovement && LockTarget)
      {
         const FRotator CurrentRotation = GetActorRotation();
         const FRotator ShouldLookRotation = FMath::RInterpTo(CurrentRotation, LockOnEnemy(), DeltaSeconds, LockRotationRate);
         GetController()->SetControlRotation(ShouldLookRotation);
      }   
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

//Set rotation
void APlayerCharacterBase::SetRotationMode(AActor* Target)
{
   LockTarget = Target;
   if (Target == nullptr)
   {
      bOrientToTheMovement = true;
      GetCharacterMovement()->bOrientRotationToMovement = true;
      bUseControllerRotationYaw = false;
   }
   else
   {
      bOrientToTheMovement = false;
      GetCharacterMovement()->bOrientRotationToMovement = false;
      bUseControllerRotationYaw = true;
   }
}
//LockOnEnemy
FRotator APlayerCharacterBase::LockOnEnemy() const
{
   FRotator LookAtRotation{0.f};
   if (LockTarget != nullptr)
   {
      // Get the locations of both actors
      const FVector SourceLocation = GetActorLocation();
      const FVector TargetLocation = LockTarget->GetActorLocation();

      // Calculate the direction vector
      const FVector Direction = (TargetLocation - SourceLocation).GetSafeNormal();

      // Create a rotator from the direction vector
      LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
   }
   return LookAtRotation;
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
int32 APlayerCharacterBase::GetPlayerLevel_Implementation()
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);

   return MainPlayerState->GetPlayerLevel();
}



void APlayerCharacterBase::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
   AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   MainPlayerState->AddToLevel(InPlayerLevel);
}
int32 APlayerCharacterBase::FindLevelForXP_Implementation(int32 InXP) const
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   return MainPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}
void APlayerCharacterBase::LevelUp_Implementation()
{
   MulticastLevelUpCues();
}

void APlayerCharacterBase::MulticastLevelUpCues_Implementation() const
{
   if (IsValid(LevelUpParticle) && IsValid(LevelUpSound))
   {
      LevelUpParticle->Activate(true);
      UGameplayStatics::PlaySound2D(this, LevelUpSound);
   }
}
//XP
void APlayerCharacterBase::AddToXP_Implementation(int32 InXP)
{
   AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);

   MainPlayerState->AddToXP(InXP);
}
int32 APlayerCharacterBase::GetXP_Implementation() const
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   return MainPlayerState->GetXP();
}

//Attribute points
void APlayerCharacterBase::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
   AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   MainPlayerState->AddToAttributePoint(InAttributePoints);
}

int32 APlayerCharacterBase::GetAttributePoint_Implementation() const
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   return MainPlayerState->GetAttributePoint();
}

int32 APlayerCharacterBase::GetAttributePointsReward_Implementation(int32 Level) const
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   check(MainPlayerState);
   return MainPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
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
void APlayerCharacterBase::SpawnWeapons(int32 Index)
{
   AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   if (MainPlayerState && MainPlayerState->WeaponInventory.Num() > Index)
   {
      //Interface Values
      const FTransform SpawnTransform{GetCombatSocketTransform()};
      APlayerWeaponBase* DefaultWeapon = GetWorld()->SpawnActorDeferred<APlayerWeaponBase>(MainPlayerState->WeaponInventory[Index], SpawnTransform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
      DefaultWeapon->FinishSpawning(SpawnTransform);
      // Attach the weapon
      if(Index ==0)
      {
         SetWeaponAttachments(DefaultWeapon, WeaponSocketName);
         MainPlayerState->EquippedWeapon1 = DefaultWeapon;
         PrimaryWeapon = DefaultWeapon;
      }
      else
      {
         MainPlayerState->EquippedWeapon2 = DefaultWeapon;
         SetWeaponAttachments(DefaultWeapon, BackSocketName);
      }
   }
}
void APlayerCharacterBase::SetWeaponAttachments(AWeaponBase* Weapon, FName Socket) const
{
   if(Weapon == nullptr) return;
   // Get the Hand Socket
   if (const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(Socket))
   {
      // Attach the Weapon to the hand socket RightHandSocket
      Weapon->SetWeaponState_Implementation(EWeaponState::State_Equipped);
      HandSocket->AttachActor(Weapon, GetMesh());  
   }
}

void APlayerCharacterBase::SwapWeapons()
{
   const AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
   if (!MainPlayerState->EquippedWeapon1 || !MainPlayerState->EquippedWeapon2)
   {
      return;
   }
   AWeaponBase* OldWeapon{nullptr};
   if (PrimaryWeapon == MainPlayerState->EquippedWeapon1)
   {
      // Swap to Weapon2
      SetWeaponAttachments(MainPlayerState->EquippedWeapon1, TEXT("BackSocket"));
      SetWeaponAttachments(MainPlayerState->EquippedWeapon2, TEXT("RightHandSocket"));
      OldWeapon = MainPlayerState->EquippedWeapon1;
      PrimaryWeapon = MainPlayerState->EquippedWeapon2;
   }
   else if (PrimaryWeapon == MainPlayerState->EquippedWeapon2)
   {
      // Swap to Weapon1
      SetWeaponAttachments(MainPlayerState->EquippedWeapon2, TEXT("BackSocket"));
      SetWeaponAttachments(MainPlayerState->EquippedWeapon1, TEXT("RightHandSocket"));
      OldWeapon = MainPlayerState->EquippedWeapon2;
      PrimaryWeapon = MainPlayerState->EquippedWeapon1;
   }
   UpdateWeaponAbilities(OldWeapon);
}

void APlayerCharacterBase::UpdateWeaponAbilities(const AWeaponBase* Weapon) const
{
   UMainAbilitySystemComponent* DarkUnitASC = Cast<UMainAbilitySystemComponent>(AbilitySystemComponent);
   if (!HasAuthority() || Weapon == nullptr || PrimaryWeapon == nullptr) return;
   DarkUnitASC->RemoveWeaponAbilities(Weapon->EssenseBond);
   DarkUnitASC->RemoveWeaponAbilities(Weapon->GuardingSigil);
   DarkUnitASC->AddWeaponAbilities(PrimaryWeapon->EssenseBond);
   DarkUnitASC->AddWeaponAbilities(PrimaryWeapon->GuardingSigil);
}
//


