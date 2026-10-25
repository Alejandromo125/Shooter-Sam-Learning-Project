// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackBoardValue.h"
#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackBoardValue::UBTTask_ClearBlackBoardValue()
{
	NodeName = TEXT("ClearValue NODE");

}

EBTNodeResult::Type UBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* bb_component = OwnerComp.GetBlackboardComponent();
	if (bb_component)
	{
		bb_component->ClearValue(GetSelectedBlackboardKey());
	}
	
	return EBTNodeResult::Succeeded;
}
