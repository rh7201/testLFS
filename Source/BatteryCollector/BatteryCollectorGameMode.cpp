// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	//NOTE: Just added this, required because this inherits from AGameModeBase not AGameMode
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	decayRate = 0.01f;
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABatteryCollectorCharacter* thePlayer = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (thePlayer)
	{
		if (GetCurrentGameState() == EGameStates::EPlaying)
		{
			if (thePlayer->GetCurrentPower() >= GetPowerAmountToWin())
			{
				SetCurrentGameState(EGameStates::EWon);
				SetSpawnVolumesActivity(false);
				DisablePlayerInput();
			}
			else if (thePlayer->GetCurrentPower() > 0)
			{
				float decayAmount = -1.0f * (thePlayer->GetInitialPower() * decayRate * DeltaTime);
				thePlayer->UpdatePowerAndStat(decayAmount);
			}
			else
			{
				SetCurrentGameState(EGameStates::EGameOver);
				SetSpawnVolumesActivity(false);
				DisablePlayerInput();

				//NOTE: Activate character's ragdoll so it will fall
				ACharacter* theCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
				if (theCharacter)
				{
					theCharacter->GetMesh()->SetSimulatePhysics(true);
					theCharacter->GetMovementComponent()->MovementState.bCanJump = false;
				}
			}
		}
	}
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	ActivateBatterySpawner();

	SetCurrentGameState(EGameStates::EPlaying);

	ABatteryCollectorCharacter* thePlayer = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (thePlayer)
	{
		powerAmountToWin = thePlayer->GetInitialPower() * 1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (currentWidget != nullptr)
		{
			currentWidget->AddToViewport();
		}
	}


}

float ABatteryCollectorGameMode::GetPowerAmountToWin() const
{
	return powerAmountToWin;
}

EGameStates ABatteryCollectorGameMode::GetCurrentGameState() const
{
	return currentGameState;
}

void ABatteryCollectorGameMode::SetCurrentGameState(EGameStates newGameState)
{
	currentGameState = newGameState;
}

void ABatteryCollectorGameMode::SetSpawnVolumesActivity(bool newState)
{
	for (ASpawnVolume* theSpawnVolume : spawnVolumeActors)
	{
		theSpawnVolume->SetSpawningState(newState);
	}
}

void ABatteryCollectorGameMode::ActivateBatterySpawner()
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), foundActors);

	for (auto actor : foundActors)
	{
		ASpawnVolume* spawnVolume = Cast<ASpawnVolume>(actor);
		if (spawnVolume)
		{
			spawnVolumeActors.AddUnique(spawnVolume);
		}
	}

	SetSpawnVolumesActivity(true);
}

void ABatteryCollectorGameMode::DisablePlayerInput()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	
	if (playerController)
	{
		playerController->SetCinematicMode(true, false, false, true, true);
	}
}