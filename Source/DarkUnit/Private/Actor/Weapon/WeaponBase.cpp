#include "Actor/Weapon/WeaponBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "DarkUnit/DarkUnitLogChannels.h"


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

	// Create and configure the capsule component
	DamageCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DamageCapsule"));
	DamageCapsule->SetupAttachment(WeaponMesh, FName("Center"));
	DamageCapsule->SetCollisionResponseToAllChannels(ECR_Overlap);
	DamageCapsule->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::PerformTrace);
	DamageCapsule->SetGenerateOverlapEvents(false);
	
	SetWeaponState(EWeaponState::State_Equipped);

 	//
	// Initialize the Niagara component but do not auto activate it
	TrailEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailEffectComponent"));
	TrailEffectComponent->SetupAttachment(WeaponMesh, FName("Center"));
	TrailEffectComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		DamageCapsule->IgnoreActorWhenMoving(this, true);
		DamageCapsule->IgnoreActorWhenMoving(GetOwner(), true);
	}
	// Setup collisions
	HitActors.Empty();  // Ensure set is empty at the start
	SetWeaponLevel(1);
	SetWeaponCollision(false);
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AWeaponBase::SetWeaponCollision(bool bCanHit)
{
	bCanHitChar = bCanHit;  // Store the collision state

	if (!bCanHit)
	{
		DamageCapsule->SetGenerateOverlapEvents(false);
		HitActors.Empty();  // Clear hit actors when stopping collision checks
		if (TrailEffectComponent)
		{
			TrailEffectComponent->Deactivate();
			// TrailEffectComponent->DestroyComponent();
		}
	}
	else
	{
		DamageCapsule->SetGenerateOverlapEvents(true);
		if (TrailEffectSystem)
		{
			TrailEffectComponent->SetAsset(TrailEffectSystem);
			TrailEffectComponent->Activate(true);

		}
	}
}

void AWeaponBase::PerformTrace(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!WeaponMesh || !DamageEffectSpecHandle.IsValid() || !Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponMesh, DamageEffectSpecHandle, or Owner is invalid."));
		return;
	}
	const bool bIsPlayer{ GetOwner()->ActorHasTag("Player") };
	if ((bIsPlayer && OtherActor->ActorHasTag("Player")) || (!bIsPlayer && OtherActor->ActorHasTag("Enemy"))) return;
	if (OtherActor && !HitActors.Contains(OtherActor))
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
			// Play impact effects
			if (ImpactSound && ImpactEffect)
			{
				// const FVector SpawnLocation = SweepResult.ImpactPoint;
				const FVector SpawnLocation = OtherActor->GetActorLocation();
				const FRotator SpawnRotation = SweepResult.ImpactNormal.Rotation();
				UE_LOG(LogDarkUnit, Error, TEXT("The Location is : %s"), *SpawnLocation.ToString());
				MulticastPlayImpactEffects(SpawnLocation, SpawnRotation);
			}
			HitActors.Add(OtherActor);  // Add actor to set so it won't be hit again until cleared
		}
	}
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
		WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case EWeaponState::State_Dropped:
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		WeaponMesh->SetVisibility(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		WeaponMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		GetWorld()->GetTimerManager().SetTimer(DropTimer, this, &AWeaponBase::DropPhysics, 0.1f, false);
		Dissolve();
		break;
	}
}
	
void AWeaponBase::DropPhysics()
{
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
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

