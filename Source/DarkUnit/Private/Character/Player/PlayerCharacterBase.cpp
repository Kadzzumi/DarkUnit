// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Character/Player/Components/VitalComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/EnemyCharacterBase.h"
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

	//Vital Component
	VitalComponent = CreateDefaultSubobject<UVitalComponent>(TEXT("VitalComponent"));
	VitalComponent->SetIsReplicated(true);
	
/*
	//Collisions
	LeftHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCollision"));
	LeftHandCollision->SetupAttachment(GetMesh(), TEXT("LeftHandSocket"));
	LeftHandCollision->SetSphereRadius(14.f);
	LeftHandCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapBeginLeftHand);
	LeftHandCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapEndLeftHand);
	LeftHandCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	LeftHandCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	RightHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCollision"));
	RightHandCollision->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	RightHandCollision->SetSphereRadius(14.f);
	RightHandCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapBeginRightHand);
	RightHandCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapEndRightHand);
	RightHandCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	RightHandCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	LeftLegCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftLegCollision"));
	LeftLegCollision->SetupAttachment(GetMesh(), TEXT("LeftLegSocket"));
	LeftLegCollision->SetSphereRadius(32.f);
	LeftLegCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::APlayerCharacterBase::OnOverlapBeginLeftLeg);
	LeftLegCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapEndLeftLeg);
	LeftLegCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	LeftLegCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RightLegCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightLegCollision"));
	RightLegCollision->SetupAttachment(GetMesh(), TEXT("RightLegSocket"));
	RightLegCollision->SetSphereRadius(32.f);
	RightLegCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapBeginRightLeg);
	RightLegCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapEndRightLeg);
	RightLegCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	RightLegCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
*/
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

void APlayerCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (VitalComponent)
	{
		VitalComponent->Player = this;
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




//
//BeginPlay and Tick
//
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	EquipWeapon(SpawnDefaultWeapon());
}


void APlayerCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	// Orient Rotation
	if (GetSpeed() <= 0.f)
	{
		SetRotation(true, false);
	}
	else
	{
		SetRotation(false, true);
	}
	
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
	if (AWeaponBase* Item = Cast<AWeaponBase>(OtherActor))
	{
		InteractingActorList.AddUnique(Item);
	}
}

void APlayerCharacterBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AWeaponBase* Item = Cast<AWeaponBase>(OtherActor))
	{
		InteractingActorList.Remove(Item);
	}
}

AWeaponBase* APlayerCharacterBase::SpawnDefaultWeapon()
{
	// Check the TSubclassOf variable
	if (WeaponBase)
	{
		// Spawn the Weapon
		PrimaryWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponBase);
		PrimaryWeapon->SetOwner(this);
		return PrimaryWeapon;
	}

	return nullptr;
}

void APlayerCharacterBase::EquipWeapon(AWeaponBase* WeaponToEquip, bool bSwapping)
{
	if (WeaponToEquip)
	{
		// Get the Hand Socket
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
		if (HandSocket)
		{
			// Attach the Weapon to the hand socket RightHandSocket
			HandSocket->AttachActor(WeaponToEquip, GetMesh());
			PrimaryWeapon = WeaponToEquip;
			PrimaryWeapon->SetWeaponState(EWeaponState::EquippedState);
		}
	}
}

void APlayerCharacterBase::SetAttackCollisions(const int32 Index)
{
	if (PrimaryWeapon)
	{
		switch (Index)
		{
		case 0:
			PrimaryWeapon->SetWeaponCollision(false);
			break;
		case 1:
			PrimaryWeapon->SetWeaponCollision(true);
			break;
		default:
			PrimaryWeapon->SetWeaponCollision(false);
			break;
		}
		
	}
}


/*
//
// Attack Collision
void APlayerCharacterBase::SetAttackCollisions(const int32 Index)
{
	switch (Index)
	{
	case 0:
		LeftHandCollision->SetGenerateOverlapEvents(false);
		RightHandCollision->SetGenerateOverlapEvents(false);
		LeftLegCollision->SetGenerateOverlapEvents(false);
		RightLegCollision->SetGenerateOverlapEvents(false);
		break;
	case 1:
		LeftHandCollision->SetGenerateOverlapEvents(true);
		break;
	case 2:
		RightHandCollision->SetGenerateOverlapEvents(true);
		break;
	case 3:
		LeftLegCollision->SetGenerateOverlapEvents(true);
		break;
	case 4:
		RightLegCollision->SetGenerateOverlapEvents(true);
		break;
	default:
		LeftHandCollision->SetGenerateOverlapEvents(false);
		RightHandCollision->SetGenerateOverlapEvents(false);
		LeftLegCollision->SetGenerateOverlapEvents(false);
		RightLegCollision->SetGenerateOverlapEvents(false);
		break;;
	}

} 

//
//Overlap event
//
void APlayerCharacterBase::OnOverlapBeginLeftHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Left Hand Begin Overlap"));
        }
		SetAttackCollisions(0);
	}

}

void APlayerCharacterBase::OnOverlapEndLeftHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Left Hand End Overlap"));
		}
	}

}

void APlayerCharacterBase::OnOverlapBeginRightHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Right Hand Begin Overlap"));
		}
		SetAttackCollisions(0);
	}

}

void APlayerCharacterBase::OnOverlapEndRightHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Right Hand End Overlap"));
		}
	}

}

void APlayerCharacterBase::OnOverlapBeginLeftLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Left Leg Begin Overlap"));
		}
		SetAttackCollisions(0);
	}

}

void APlayerCharacterBase::OnOverlapEndLeftLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Left Leg End Overlap"));
		}
	}

}

void APlayerCharacterBase::OnOverlapBeginRightLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Right Leg Begin Overlap"));
		}
		SetAttackCollisions(0);
	}

}

void APlayerCharacterBase::OnOverlapEndRightLeg(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Right Leg End Overlap"));
		}
	}

}
*/
