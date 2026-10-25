// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERSAM_API AShooterAI : public AAIController
{
	GENERATED_BODY()
protected:
	/** Gameplay initialization */
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartBehaviourTree(AShooterSamCharacter* player);

public:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* enemyAI_BT;

	AShooterSamCharacter* playerCharacter;
	AShooterSamCharacter* myCharacter;

	
};
