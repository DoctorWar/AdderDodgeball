// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "MyBallClass.h"
#include "Ad_CharacterAIComponent.h"
#include "Camera.h"
#include "Adder_DodgeBallCharacter.generated.h"

UCLASS(Blueprintable)
class AAdder_DodgeBallCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:
	/** AI Component used for AI characters, turns off if player controlled */
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UAd_CharacterAIComponent* AIComponent;


public:
	AAdder_DodgeBallCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERASTUFF)
		ACamera* StaticCamera;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = powerUp)
		TEnumAsByte<PowerUp::PowerUpType> currentPowerup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool isAI;
	//set this to true when hit by the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool isAlive;
	//used to check how long since a character was hit, add deltatime when dead
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float downTime;

	//give a reference to the ball last controlled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		AMyBallClass* ballRef;
	//pass isThrowing to the anim. component to show throw animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool isThrowing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float throwPower;

	UFUNCTION(BlueprintCallable, Category = AI)
		virtual void WindUp();
	UFUNCTION(BlueprintCallable, Category = AI)
		virtual void ThrowBall();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};

