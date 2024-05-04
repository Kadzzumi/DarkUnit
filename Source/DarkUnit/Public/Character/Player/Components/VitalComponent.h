// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Player/PlayerCharacterBase.h"
#include "VitalComponent.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKUNIT_API UVitalComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVitalComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	friend class APlayerCharacterBase;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Gas system Stamina
	void ApplyEffectToTheTarget();

	//GAS Stamina Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> StaminaGameplayEffectClass;
private:
	//Character
	APlayerCharacterBase* Player;


public:	
	

		
};
