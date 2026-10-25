// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AShooterAI::StartBehaviourTree(AShooterSamCharacter* player)
{
	if (enemyAI_BT)
	{
		myCharacter = Cast<AShooterSamCharacter>(GetPawn());
		if (player)
		{
			playerCharacter = player;
		}
		RunBehaviorTree(enemyAI_BT);
		UBlackboardComponent* myBlackBoard = GetBlackboardComponent();
		if (myBlackBoard)
		{
			if (myCharacter)
				myBlackBoard->SetValueAsVector("StartingLocation", myCharacter->GetActorLocation());
		}
	}
}
