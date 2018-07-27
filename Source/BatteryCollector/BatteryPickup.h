// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	ABatteryPickup();

	void GetCollected_Implementation() override;

	float GetPower();
	
protected:

	//NOTE: Enabled BlueprintProtected means this variable can only be accessed by blueprints that inherit this class' blueprint, but Editanywhere also make it accessible by this BP in editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float batteryPower;
	
};
