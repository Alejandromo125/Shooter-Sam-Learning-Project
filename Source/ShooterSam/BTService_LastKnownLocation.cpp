// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LastKnownLocation.h"
#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_LastKnownLocation::UBTService_LastKnownLocation()
{
	NodeName = TEXT("LastKnownLocation NODE");

}

void UBTService_LastKnownLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AShooterAI* ownerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	if (ownerController)
	{
		AShooterSamCharacter* player = ownerController->playerCharacter;
		UBlackboardComponent* bb_component = ownerController->GetBlackboardComponent();
		if (bb_component && player)
		{
			if (ownerController->LineOfSightTo(player))
			{
				bb_component->SetValueAsVector(GetSelectedBlackboardKey(), player->GetActorLocation());
			}
		}
	}
}
