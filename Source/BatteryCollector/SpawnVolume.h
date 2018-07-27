// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UBoxComponent* GetSpawnPoint() const { return spawnPoint; }

	//NOTE:Get random location within spawn cubic area
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomLocationInVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void resetSpawnTiming();

	//NOTE: TSubClassOf allow us to use sub class of mentioned class here, in this case BatteryPickUp
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> spawnObject;

	FTimerHandle spawnTimer;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Spawning")
	float spawnDelayRangeLow;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Spawning")
	float spawnDelayRangeHigh;
	
private:
	void SpawnPickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* spawnPoint;

	//NOTE:Actual spawn delay
	float spawnDelay;
	
};
