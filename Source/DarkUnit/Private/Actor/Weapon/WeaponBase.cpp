// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponBase.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/Enemy/EnemyCharacterBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
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
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
	WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &AWeaponBase::OnOverlapEnd);
	WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	WeaponCollision->SetGenerateOverlapEvents(true);
}

void AWeaponBase::SetWeaponCollision(bool bCanHit) const
{
	WeaponCollision->SetGenerateOverlapEvents(bCanHit);
}


void AWeaponBase::SetWeaponState(EWeaponState NewState)
{
	if (CurrentState != NewState)
	{
		CurrentState =	NewState; 

	}
}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Did Overlap"));
		}
		if (ImpactSound && ImpactEffect)
		{
			const FVector SpawnLocation = SweepResult.Location;
			const FRotator SpawnRotation = FRotationMatrix::MakeFromZ(SweepResult.ImpactNormal).Rotator();
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, SpawnLocation);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, SpawnLocation, SpawnRotation);
			SetWeaponCollision(false);
		}

	}
}

void AWeaponBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("End Overlap"));
		}
		SetWeaponCollision(false);
	}	
}



