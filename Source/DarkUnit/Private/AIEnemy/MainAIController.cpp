// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy/MainAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMainAIController::AMainAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);

	EnemyBehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BegaviorTreeComponent");
	check(EnemyBehaviorTreeComponent);
}
