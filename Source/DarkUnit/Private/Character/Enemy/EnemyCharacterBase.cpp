// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacterBase.h"
#include "DarkUnitGameplayTags.h"
#include "AbilitySystem/DarkUnitAbilitySystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Actor/Weapon/WeaponBase.h"
#include "AIEnemy/MainAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/MainUserWidget.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//GAS
	AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// Rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll  = false;
	bUseControllerRotationYaw   = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	AttributeSet = CreateDefaultSubobject<UMainAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidget");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEnemyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return;
	
	MainAIController = Cast<AMainAIController>(NewController);

	MainAIController->GetBlackboardComponent()->InitializeBlackboard(*MainBehaviorTree->BlackboardAsset);
	MainAIController->RunBehaviorTree(MainBehaviorTree);
	MainAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	MainAIController->GetBlackboardComponent()->SetValueAsEnum(FName("EnemyType"), static_cast<uint8>(CharacterClass));
	MainAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), bIsDead);
}

int32 AEnemyCharacterBase::GetPlayerLevel_Implementation()
{
	return Level;
}


ECharacterClass AEnemyCharacterBase::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UDarkUnitAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
		MainAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
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

void AEnemyCharacterBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (HasAuthority())
	{
		MainAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void AEnemyCharacterBase::Die()
{
	SetLifeSpan(LifeSpanTime);
	bIsDead = true;
	MainAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), bIsDead);
	Super::Die();
}
//
//Combat
//
void AEnemyCharacterBase::SetCombatTarget_Implementation(AActor* InCombatTaget)
{
	CombatTarget = InCombatTaget;
}

AActor* AEnemyCharacterBase::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

FVector AEnemyCharacterBase::GetLookLocation()
{
	if (CombatTarget != nullptr && CombatTarget->ActorHasTag("Player"))
	{
		return CombatTarget->GetActorLocation();
	}
	return FVector();
}