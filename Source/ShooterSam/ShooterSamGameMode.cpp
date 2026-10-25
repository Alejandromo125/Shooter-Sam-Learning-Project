// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAI.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();
	AShooterSamCharacter* playerPawn = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);

	for (AActor* actor : ShooterAIActors)
	{
		AShooterAI* shooterAI = Cast<AShooterAI>(actor);
		if(shooterAI)
		{
			shooterAI->StartBehaviourTree(playerPawn);
		}
	}


}
