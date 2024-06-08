// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacterBase.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/DarkUnitAbilitySystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/MainUserWidget.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//GAS
	AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UMainAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidget");
	HealthBar->SetupAttachment(GetRootComponent());
}

int32 AEnemyCharacterBase::GetPlayerLevel()
{
	return Level;
}


void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();
	UDarkUnitAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	
	// Widget for health
	if (UMainUserWidget* MainUserWidget = Cast<UMainUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		MainUserWidget->SetWidgetController(this);
	}
	if (const UMainAttributeSet* DarkUnitAS = Cast<UMainAttributeSet>(AttributeSet))
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DarkUnitAS->GetHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					OnHealthChange.Broadcast(Data.NewValue);
				}
			);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DarkUnitAS->GetMaxHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					OnMaxHealthChange.Broadcast(Data.NewValue);
				}
			);
		
		// listen for the added or removed tags
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FDarkUnitGameplayTags::Get().Effect_HitReactSmall, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AEnemyCharacterBase::HitReactTagChanged);
		
		OnHealthChange.Broadcast(DarkUnitAS->GetHealth());
		OnMaxHealthChange.Broadcast(DarkUnitAS->GetMaxHealth());
	}
}

void AEnemyCharacterBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMainAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}

void AEnemyCharacterBase::InitializeDefaultAttributes() const
{
	UDarkUnitAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AEnemyCharacterBase::SetWeaponAttachment(AWeaponBase* Weapon)
{
	if(Weapon == nullptr) return;
	// Get the Hand Socket
	if (const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(WeaponSocketName))
	{
		// Attach the Weapon to the hand socket RightHandSocket
		HandSocket->AttachActor(Weapon, GetMesh());
	}
}

float AEnemyCharacterBase::CalculateOveralldDamage()
{
	return BonusDamage;
}

void AEnemyCharacterBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}
