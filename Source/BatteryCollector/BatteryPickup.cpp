// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);

	//NOTE: set default battery power
	batteryPower = 150.0f;
}

void ABatteryPickup::GetCollected_Implementation()
{
	Super::GetCollected_Implementation();

	Destroy();
}

float ABatteryPickup::GetPower()
{
	return batteryPower;
}




