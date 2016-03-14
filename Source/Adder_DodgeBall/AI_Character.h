// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Ad_CharacterAIComponent.h"
#include "AI_Character.generated.h"

UCLASS()
class ADDER_DODGEBALL_API AAI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	/** AI Component used for AI characters, turns off if player controlled */
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UAd_CharacterAIComponent* AIComponent;
/*
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	FVector targetPoint;
	//Time between AI decisions in seconds, currently used for wander only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float AITimeStep;
	//Counter to go with time step
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float AITimer;
	//Could be a navmesh or just an empty cube object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	AActor* targetRegion;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		FVector boundsPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		FVector boundsVector;
	
	*/
};
