// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyAnimInstance.h"


#include "Character/Enemy/EnemyCharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


UEnemyAnimInstance::UEnemyAnimInstance():
	Enemy(nullptr),
	Speed(0),
	Direction(0),
	bCrouching(false),
	bInAir(false)
{
	
}

void UEnemyAnimInstance::LocalNativeUpdateAnimation(float DeltaTime)
{
	if (Enemy == nullptr)
	{
		Enemy = Cast<AEnemyCharacterBase>(TryGetPawnOwner());
	}
	if (Enemy)
	{
		//Speed
		FVector Velocity{Enemy->GetVelocity()};
		Velocity.Z = 0.f;
		Speed = Velocity.Size();
		// Direction
		const auto AimRotation = Enemy->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		if (bInAir)
		{

		}
	}
}
