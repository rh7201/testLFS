// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;
	
protected:

	//NOTE: "Edit defaults only" only allows us to edit on constructor not on instance 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	//NOTE: this is the rate the main character loses power over the time
	float decayRate;
};



