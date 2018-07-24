// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Pickup.generated.h"
// NOTE: Don't add any .h after .generated.h

/*
NOTE: 

If it compiles correctly, even when IntelliSense is complaining, do this:

Change to DevelopmentEditor configuration, compile; Change to DevelopmentGame configuration, compile. This gets IntelliSense to recompile and rescan headers and everything works fine again.

This often happens when you alter the lines in your .h code, above the declaration of UCLASS but it can affect other types too.
*/


UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickUpMesh; }

private:

	//NOTE: Static mesh that represent visual pick up on the level
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickUpMesh;
		
	
};
