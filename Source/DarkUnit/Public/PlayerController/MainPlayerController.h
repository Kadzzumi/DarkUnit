// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


class UDarkUnitInputConfig;
class APlayerCharacterBase;
class UInputMappingContext;
class UInputAction;
class UMainAbilitySystemComponent;

UCLASS()
class DARKUNIT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainPlayerController();
	void PlayerJump();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;
	//Input Actions
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;


	//Controller
	UPROPERTY()
	APlayerCharacterBase* ControlledPawn;

	//Action Functions
	void Move(const struct FInputActionValue& InputActionValue);
	void Look(const struct FInputActionValue& InputActionValue);
	
	//
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	void AbilityInputHeld(FGameplayTag InputTag);
	
	//
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UDarkUnitInputConfig> DarkUnitInputConfig;

	UPROPERTY()
	TObjectPtr<UMainAbilitySystemComponent> DarkUnitAbilitySystemComponent;
	UMainAbilitySystemComponent* GetASC();
};
