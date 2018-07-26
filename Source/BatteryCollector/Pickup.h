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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickUpMesh; }

	//NOTE: BlueprintPure doesn't change value of variable, while BlueprintCAllable may change value and must reside in execution chain
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool GetIsActive();

	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool GetAlwaysActive();

	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool GetAlwaysInActive();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetIsActive(bool thePickUpState);

	UFUNCTION(BlueprintNativeEvent)
	void GetCollected();	//NOTE: this will be called by character code, blueprint native event will automatically call _implementation, when the public method is called
	virtual void GetCollected_Implementation();		//NOTE: this is actual implementation called, to be done in child class

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//NOTE: false when pick up is consumed and deactivated
	bool isActive;

private:

	//NOTE: Static mesh that represent visual pick up on the level
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickUpMesh;
		
	
};
