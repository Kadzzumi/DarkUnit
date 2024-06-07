// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Items/ItemBase.h"

#include "Components/SphereComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	SetRootComponent(CollisionSphere);
	CollisionSphere->SetCollisionObjectType(ECC_EngineTraceChannel1);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}


