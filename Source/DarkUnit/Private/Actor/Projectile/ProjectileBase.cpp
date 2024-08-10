// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/ProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	
	//Movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->ProjectileGravityScale = 0.05f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(ProjectileLifeSpan);
	Sphere->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AProjectileBase::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		LoopingSoundComponent->Stop();
	}
	Super::Destroyed();	
}


void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	bool bIsPlayer{true};
	if (!DamageEffectSpecHandle.Data.IsValid() || DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor)
	{
		return;
	}
	if (GetOwner()->ActorHasTag("Player"))
	{
		bIsPlayer = true;
	}
	else
	{
		bIsPlayer = false;
	}
	if (ImpactSound && ImpactEffect)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}
	if (HasAuthority())
	{
		if((bIsPlayer && OtherActor->ActorHasTag("Player")) || (!bIsPlayer && OtherActor->ActorHasTag("Enemy")))
		{
			//Do nothing
			Destroy();
			return;
		}
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

