// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"
#include "Gun.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot NODE");

}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AShooterAI* ownerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());

	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	if (ownerController)
	{
		AShooterSamCharacter* playerCharacter = ownerController->playerCharacter;
		AShooterSamCharacter* myCharacter = ownerController->myCharacter;

		if (myCharacter && playerCharacter && playerCharacter->isAlive)
		{
			myCharacter->ShootAI();
			AGun* characterGun = myCharacter->gunActorPointer;

			characterGun->PullTrigger();
			Result = EBTNodeResult::Succeeded;


		}
	}

	return Result;

}
