// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class APlayerCharacterBase;
class USphereComponent;
class APlayerWeaponBase;

UCLASS()
class DARKUNIT_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();
	virtual void Interact(APlayerCharacterBase* Player);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;
};
