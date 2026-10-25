// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("PlayerLocation NODE");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
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
				ownerController->SetFocus(player);
				
			}
			else
			{
				bb_component->ClearValue(GetSelectedBlackboardKey());

				ownerController->ClearFocus(EAIFocusPriority::Gameplay);
			}
		}
	}
		

	
	
}
