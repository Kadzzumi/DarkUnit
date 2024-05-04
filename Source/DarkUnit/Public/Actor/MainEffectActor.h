// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "MainEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

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
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	bool bDestroyOnEffectRemoval = true;
	
// Effects application policy
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	EEffectApplicationPolicy InstantEffectAplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	EEffectApplicationPolicy DurationEffectAplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	EEffectApplicationPolicy InfiniteEffectAplicationPolicy = EEffectApplicationPolicy::DoNotApply;

// Effects Removal policy
	
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	
//Effects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

//Actor Level
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	float ActorLevel = 1.f;
};
