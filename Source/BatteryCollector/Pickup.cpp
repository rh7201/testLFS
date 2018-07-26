// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//NOTE: default is TRUE
	PrimaryActorTick.bCanEverTick = false;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
	RootComponent = PickUpMesh;

	//NOTE: initially all pick up are active
	isActive = true;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

//NOTE: As Tick is set to false, we can delete this method 
// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickup::GetIsActive()
{
	return isActive;
}

bool APickup::GetAlwaysActive()
{
	return true;
}

bool APickup::GetAlwaysInActive()
{
	return false;
}

void APickup::SetIsActive(bool thePickupState)
{
	isActive = thePickupState;
}

void APickup::GetCollected_Implementation()
{
	//NOTE: Here we will just output debug log
	FString pickUpObjectName = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *pickUpObjectName);
}

