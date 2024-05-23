// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerAnimInstance.h"

#include "Character/Player/PlayerCharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerController/MainPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance():
	Player(nullptr),
	Speed(0),
	Direction(0),
	bCrouching(false),
	bInAir(false)
{
	
}

void UPlayerAnimInstance::LocalNativeUpdateAnimation(float DeltaTime)
{
	if (Player == nullptr)
	{
		Player = Cast<APlayerCharacterBase>(TryGetPawnOwner());
	}
	if (Player)
	{
		//Speed
		FVector Velocity{Player->GetVelocity()};
		Velocity.Z = 0.f;
		Speed = Velocity.Size();
		// Direction
		const auto AimRotation = Player->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		bInAir = Player->GetMovementComponent()->IsFalling();
		if (bInAir)
		{
			AMainPlayerController* PC = Cast<AMainPlayerController>(Player->GetController());
			if (PC)
			{
				PC->PlayerJump();
			}
		}
	}
}
