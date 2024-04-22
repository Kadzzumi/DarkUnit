// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/MainPlayerState.h"

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
}

// Init Ability Actor Info
void APlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}
void APlayerCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}
void APlayerCharacterBase::InitAbilityActorInfo()
{
	//Init Ability Actor Info For the Server
	AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
	check(MainPlayerState);
	MainPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MainPlayerState, this);
	AbilitySystemComponent = MainPlayerState->GetAbilitySystemComponent();
	AttributeSet = MainPlayerState->GetAttributeSet();
}

//
//BeginPlay and Tick
//
void APlayerCharacterBase::BeginDestroy()
{
	Super::BeginDestroy();
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


float APlayerCharacterBase::GetSpeed() const
{
	FVector Velocity{GetVelocity()};
	Velocity.Z = 0.f;
	return Velocity.Size();
}
