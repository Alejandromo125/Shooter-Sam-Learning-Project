// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERSAM_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)

	USceneComponent* sceneComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	AController* ownerController;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float bulletDamage = 10.0f;

	void PullTrigger();


	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* muzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* impactParticleSystem;
};
