// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineUtils.h" 
#include "Components/ActorComponent.h"
#include "Ad_CharacterAIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADDER_DODGEBALL_API UAd_CharacterAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAd_CharacterAIComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public: //functions
	UFUNCTION()
		virtual bool IsClosestToTarget(AActor* inTarget);

	UFUNCTION()
		virtual AActor* GetClosestTarget();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		AActor* targetActor;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		FVector boundsPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		FVector boundsVector;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		APawn* OwningPawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		APawn* PlayersPawn;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	//	bool isAI;
	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
//		bool hasBall;
};
