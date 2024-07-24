#include "Actor/Weapon/WeaponBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
AWeaponBase::AWeaponBase() :
	CapsuleRadius(10)  // Initialize here
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// Setting Root && Basics
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(RootSceneComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetWeaponState(EWeaponState::State_Equipped);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	// Setup collisions
	HitActors.Empty();  // Ensure set is empty at the start
	SetWeaponLevel(1);
	SetWeaponCollision(false);
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	 if (bCanHitChar)  // Add this check
	 {
	 	TimeSinceLastTrace += DeltaTime;
	 	if (TimeSinceLastTrace >= 0.01f)
	 	{
	 		PerformTrace();
	 		TimeSinceLastTrace = 0.f;
	 	}
	 }
}

void AWeaponBase::SetWeaponCollision(bool bCanHit)
{
	bCanHitChar = bCanHit;  // Store the collision state

	if (!bCanHit)
	{
		TimeSinceLastTrace = 0.f;
		HitActors.Empty();  // Clear hit actors when stopping collision checks
		// GetWorldTimerManager().ClearTimer(AttackTimerHandle);	
	}
	else
	{
		// GetWorldTimerManager().SetTimer(AttackTimerHandle, 0.01f, true);
	}
}

void AWeaponBase::PerformTrace()
{
	if (!WeaponMesh || !DamageEffectSpecHandle.IsValid() || !Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponMesh, DamageEffectSpecHandle, or Owner is invalid."));
		return;
	}
	// Trace Params
	FVector Start, End, Direction;
	float CapsuleHalfHeight;
	FQuat CapsuleRotation;
	SetupTraceParameters(Start, End, Direction, CapsuleHalfHeight, CapsuleRotation);

	// Collision Params
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());

	const bool bIsPlayer{ GetOwner()->ActorHasTag("Player") };

	const bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		CapsuleRotation,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
		CollisionParams
	);
	DrawDebugCapsule(GetWorld(), (Start + End) / 2.0f, CapsuleHalfHeight, CapsuleRadius, CapsuleRotation, FColor::Blue, false, 1.0f, 0, 2.0f);

	if (bHit)
	{
		for (auto& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if ((bIsPlayer && HitActor->ActorHasTag("Player")) || (!bIsPlayer && HitActor->ActorHasTag("Enemy"))) return;
			if (HitActor && !HitActors.Contains(HitActor))
			{
				if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor))
				{
					TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
					// Play impact effects
					if (ImpactSound && ImpactEffect)
					{
						const FVector SpawnLocation = Hit.ImpactPoint;
						const FRotator SpawnRotation = Hit.ImpactNormal.Rotation();
						MulticastPlayImpactEffects(SpawnLocation, SpawnRotation);
					}
					HitActors.Add(HitActor);  // Add actor to set so it won't be hit again until cleared
				}
			}
		}
	}
}

void AWeaponBase::SetupTraceParameters(FVector& Start, FVector& End, FVector& Direction, float& CapsuleHalfHeight, FQuat& CapsuleRotation) const
{
	Start = WeaponMesh->GetSocketLocation(FName("Start"));
	End = WeaponMesh->GetSocketLocation(FName("End"));
	Direction = (End - Start).GetSafeNormal();
	CapsuleHalfHeight = (End - Start).Size() - 15.f;
	CapsuleRotation = FQuat::FindBetweenVectors(FVector::UpVector, Direction);
}

void AWeaponBase::MulticastPlayImpactEffects_Implementation(const FVector& Location, const FRotator& Rotation)
{
	if (ImpactSound && ImpactEffect)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Location);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, Location, Rotation);
	}
}

// Weapon Phys Damage


void AWeaponBase::SetWeaponLevel(int32 NewWeaponLevel)
{
	WeaponLevel = FMath::Clamp(NewWeaponLevel, 1, 10);
}

float AWeaponBase::GetWeaponDamage() const
{
	return DamageCurve.GetValueAtLevel(WeaponLevel);
}

// Weapon State
void AWeaponBase::SetWeaponState_Implementation(EWeaponState State)
{
	WeaponState = State;
	switch (WeaponState)
	{
	case EWeaponState::State_Equipped:
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetEnableGravity(false);
		WeaponMesh->SetVisibility(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case EWeaponState::State_Dropped:
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		WeaponMesh->SetSimulatePhysics(true);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetVisibility(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		WeaponMesh->SetCollisionResponseToChannel(
			ECollisionChannel::ECC_WorldStatic,
			ECollisionResponse::ECR_Block);
		Dissolve();
		break;
	}
}

void AWeaponBase::Dissolve()
{
	if (IsValid(MI_WeaponDessolve))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(MI_WeaponDessolve, WeaponMesh);
		WeaponMesh->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
}