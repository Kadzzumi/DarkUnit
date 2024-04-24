// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class DARKUNIT_API AMainEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMainEffectActor();
	//Overlaps
	
	
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTheTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
//Effects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
private:
};
