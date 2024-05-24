#include "Actor/Weapon/WeaponBase.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/Enemy/EnemyCharacterBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AWeaponBase::AWeaponBase() :
	Damage(10),
	CapsuleRadius(30)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	//Setting Root && Basics
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(RootSceneComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>("WeaponCollision");
	WeaponCollision->SetupAttachment(WeaponMesh, TEXT("CollisionSocket"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	SetWeaponState(EWeaponState::WorldState);
	//Setup collisions
	WeaponCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	WeaponCollision->SetGenerateOverlapEvents(true);
	HitActors.Empty();  // Ensure set is empty at the start
}

void AWeaponBase::SetWeaponCollision(bool bCanHit)
{
	if (bCanHit)
	{
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AWeaponBase::PerformTrace, 0.015f, true, 0.f);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		HitActors.Empty();  // Clear hit actors when stopping collision checks
	}
}

void AWeaponBase::SetWeaponState(EWeaponState NewState)
{
	if (CurrentState != NewState)
	{
		CurrentState = NewState; 
	}
}

void AWeaponBase::PerformTrace()
{
	if (!WeaponMesh)
	{
		return;
	}

	const FVector Start = WeaponMesh->GetSocketLocation(FName("Start"));
	const FVector End = WeaponMesh->GetSocketLocation(FName("End"));
	const FVector TraceVector = End - Start;
	const float CapsuleHalfHeight = TraceVector.Size() / 2.0f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(Owner);

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(30.f, 110.f),
		CollisionParams
	);
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 1.0f, 0, 2.0f);

	if (bHit)
	{
		for (auto& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && Cast<AEnemyCharacterBase>(HitActor) && !HitActors.Contains(HitActor))
			{
				// Apply damage to the hit actor
				// UGameplayStatics::ApplyDamage(HitActor, Damage, nullptr, this, nullptr);
				
				// Play impact effects
				if (ImpactSound && ImpactEffect)
				{
					const FVector SpawnLocation = Hit.Location;
					const FRotator SpawnRotation = Hit.ImpactNormal.Rotation();
					UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, SpawnLocation);
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, SpawnLocation, SpawnRotation);
					HitActors.Add(HitActor);  // Add actor to set so it won't be hit again until cleared
				}
			}
		}
	}
}
