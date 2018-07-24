// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "TreeSample.h"


// Sets default values
ATreeSample::ATreeSample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATreeSample::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreeSample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

