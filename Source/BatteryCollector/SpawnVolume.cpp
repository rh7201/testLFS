// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	spawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPoint"));
	RootComponent = spawnPoint;

	spawnDelayRangeLow = 1.0f;
	spawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	resetSpawnTiming();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomLocationInVolume()
{
	FVector spawnOrigin = spawnPoint->Bounds.Origin;
	FVector spawnExtend = spawnPoint->Bounds.BoxExtent;
	
	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtend);
}

void ASpawnVolume::SpawnPickup()
{
	UWorld* const world = GetWorld();

	if (world && spawnObject != NULL)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;

		FVector spawnLocation = GetRandomLocationInVolume();
		FRotator spawnRotation;
		spawnRotation.Yaw = FMath::Rand() * 360.0f;
		spawnRotation.Pitch = FMath::Rand() * 360.0f;
		spawnRotation.Roll = FMath::Rand() * 360.0f;

		//NOTE: DON'T DELETE, another alternative on how to spawn
		//APickup* spawnedPickup = world->SpawnActor<APickup>(spawnLocation, spawnRotation, spawnParams);

		APickup* spawnedPickup = world->SpawnActor<APickup>(spawnObject, spawnLocation, spawnRotation, spawnParams);

		resetSpawnTiming();
		
	}
}

void ASpawnVolume::resetSpawnTiming()
{
	spawnDelay = FMath::FRandRange(spawnDelayRangeLow, spawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnPickup, spawnDelay, false);
}
