// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BatteryCollectorCharacter.generated.h"

UCLASS(config=Game)
class ABatteryCollectorCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//NOTE: Collection sphere added as collider sensor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* collectionSphere;
public:
	ABatteryCollectorCharacter();

	UFUNCTION(BlueprintPure, Category =  "Power")
	float GetInitialPower();

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower();

	//NOTE: The power amount can be negative or positive
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdatePowerAndStat(float thePowerAmount);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	//NOTE: This method will be called when player press a key and a pickup is inside Collection Sphere
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void CollectPickups();

	//NOTE: BlueprintImplementableEvent means we don't have to implement this method, blueprint will handle it
	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
	void showPowerChangeEffect();

	//NOTE: Editanywhere so that this property editable via code/editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float initialPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float speedFactor;

	//NOTE: This is the speed when power is drop to 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float baseSpeed;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	//NOTE: Returns collection sphere subobject
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return collectionSphere; }

private:

	UPROPERTY(VisibleAnywhere, Category = "Power")
	float currentPower;
};

