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
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AttributeMenuAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> BasicAttackAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> HeavyAttackAction;
	//Controller
	UPROPERTY()
	APlayerCharacterBase* ControlledPawn;

	//Action Functions
	void Move(const struct FInputActionValue& InputActionValue);
	void Look(const struct FInputActionValue& InputActionValue);
	void PlayerJump(const struct FInputActionValue& InputActionValue);
	void BasicAttack(const struct FInputActionValue& InputActionValue);
	void HeavyAttack(const struct FInputActionValue& InputActionValue);

	
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
