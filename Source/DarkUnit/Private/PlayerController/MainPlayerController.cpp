// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/MainPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Character/Player/PlayerCharacterBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "input/DarkUnitInputComponent.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"


AMainPlayerController::AMainPlayerController(): ControlledPawn(nullptr)
{
	bReplicates = true;
}



void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}
	ControlledPawn = Cast<APlayerCharacterBase>(GetPawn());
	SetWeaponSpecHandle();
}
//
void AMainPlayerController::SetWeaponSpecHandle()
{
	if (GetASC())
	{
		const FGameplayTag WeaponTag = FGameplayTag::RequestGameplayTag(FName("GA.SetWeaponSpecHandle"));
		FGameplayTagContainer WeaponTagContainer;
		WeaponTagContainer.AddTag(WeaponTag);
		GetASC()->TryActivateAbilitiesByTag(WeaponTagContainer);
	}
}
// Setting inputs
void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UDarkUnitInputComponent* DarkUnitInputComponent = CastChecked<UDarkUnitInputComponent>(InputComponent);
	DarkUnitInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
	DarkUnitInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Look);
	
	DarkUnitInputComponent->BindAbilityActions(DarkUnitInputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, &ThisClass::AbilityInputHeld);
	
}
// Inputs to Actions
void AMainPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (ControlledPawn)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AMainPlayerController::Look(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (ControlledPawn)
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		const float CurrentPitch = ControlledPawn->GetBaseAimRotation().Pitch;
		float BasePitch = LookAxisVector.Y;
		UE_LOG(LogTemp, Warning, TEXT("Pitch is: %f"), CurrentPitch);
		UE_LOG(LogTemp, Warning, TEXT("BasePitch is: %f"), BasePitch);
		if (CurrentPitch >= 50 && BasePitch < 0)
		{
			BasePitch = 0;
		}
		else if(CurrentPitch <= -50 && BasePitch > 0)
		{
			BasePitch = 0;
		}
		ControlledPawn->AddControllerPitchInput(BasePitch);
	}
}

//
//Bind Input
void AMainPlayerController::AbilityInputPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagPressed(InputTag);
}

void AMainPlayerController::AbilityInputReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Green, *InputTag.ToString());
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AMainPlayerController::AbilityInputHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Blue, *InputTag.ToString());
	GetASC()->AbilityInputTagHeld(InputTag);
}


UMainAbilitySystemComponent* AMainPlayerController::GetASC()
{
	if (DarkUnitAbilitySystemComponent == nullptr)
	{
		DarkUnitAbilitySystemComponent = Cast<UMainAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
		GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Yellow, TEXT("Getting AbilitySystemComponent For the first time"));
	}
	return DarkUnitAbilitySystemComponent;
}

void AMainPlayerController::PlayerJump()
{
	if (GetASC())
	{
		const FGameplayTag JumpTag = FGameplayTag::RequestGameplayTag(FName("InputTag.Jump"));
		GetASC()->AbilityInputTagPressed(JumpTag);
	}
}
// Show Damage Number
void AMainPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageText)
	{
		UDamageTextComponent* DamageTextComponent = NewObject<UDamageTextComponent>(TargetCharacter, DamageText);
		DamageTextComponent->RegisterComponent();
		DamageTextComponent->AttachToComponent(TargetCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("DamageSocket"));
		DamageTextComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageTextComponent->SetDamageText(DamageAmount);
	}
}
