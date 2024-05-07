// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class DARKUNIT_API APlayerCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacterBase();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void PostInitializeComponents() override;
	//Tick
	virtual void Tick(float DeltaSeconds) override;

	//Movement
	float GetSpeed() const;

	//Combat Interface
	virtual int32 GetPlayerLevel() override;

	//Menu
	void OpenAttributeMenu();
protected:
	
	virtual void BeginDestroy() override;
	//Movement
	void SetRotation(bool bOrientToMovement, bool Yaw);

private:
	// Functions
	virtual void InitAbilityActorInfo() override;
	//Camera Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FRotator ZAxisRotation{FRotator(0.f, 540.f, 0.f)};
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UVitalComponent* VitalComponent;


};
