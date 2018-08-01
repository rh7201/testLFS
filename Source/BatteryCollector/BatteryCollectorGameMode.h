// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameStates : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerAmountToWin() const;

	UFUNCTION(BlueprintPure, Category = "Game State")
	EGameStates GetCurrentGameState() const;

	void SetCurrentGameState(EGameStates newGameState);
	
protected:

	//NOTE: "Edit defaults only" only allows us to edit on constructor not on instance 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	//NOTE: this is the rate the main character loses power over the time
	float decayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float powerAmountToWin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* currentWidget;

private:
	EGameStates currentGameState;
};



