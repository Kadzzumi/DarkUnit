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
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

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
	if (HasAuthority())
	{
		UDarkUnitAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}

	
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
		
		if (AbilitySystemComponent)
		{
			const FGameplayTag WeaponTag = FGameplayTag::RequestGameplayTag(FName("InputTag.SpawnDefaultWeapon"));
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(WeaponTag);
			AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
		}
	}
}

void AEnemyCharacterBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMainAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void AEnemyCharacterBase::InitializeDefaultAttributes() const
{
	UDarkUnitAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AEnemyCharacterBase::SetWeaponAttachment(AWeaponBase* Weapon)
{
	Super::SetWeaponAttachment(Weapon);
}

float AEnemyCharacterBase::CalculateOveralldDamage()
{
	return BonusDamage;
}

void AEnemyCharacterBase::Die()
{
	SetLifeSpan(LifeSpanTime);
	Super::Die();
}

void AEnemyCharacterBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}
