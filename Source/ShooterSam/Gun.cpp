// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(sceneComponent);

	skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	skeletalMeshComponent->SetupAttachment(sceneComponent);

	muzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleComponent"));
	muzzleFlashParticleSystem->SetupAttachment(skeletalMeshComponent);
}


// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	muzzleFlashParticleSystem->Deactivate();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	muzzleFlashParticleSystem->Activate(true);

	if (ownerController)
	{
		FVector location;
		FRotator rotation;
		ownerController->GetPlayerViewPoint(location,rotation);

		FVector endlocation = location + rotation.Vector() * MaxRange;
		FHitResult hitResult;
		FCollisionQueryParams collisionQueryParams;
		bool hit;
		collisionQueryParams.AddIgnoredActor(this);
		collisionQueryParams.AddIgnoredActor(GetOwner());
		hit = GetWorld()->LineTraceSingleByChannel(hitResult, location, endlocation, ECollisionChannel::ECC_GameTraceChannel2, collisionQueryParams);
		if (hit)
		{	
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), impactParticleSystem, hitResult.ImpactPoint,hitResult.ImpactPoint.Rotation());
			UGameplayStatics::ApplyDamage(hitResult.GetActor(), bulletDamage, ownerController, ownerController->GetInstigatorController(), UDamageType::StaticClass());
		}
	}
}

