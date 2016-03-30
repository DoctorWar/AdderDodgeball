// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Adder_DodgeBallCharacter.h"
#include "MyBallClass.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "PowerUpPickUp.generated.h"

UCLASS()
class ADDER_DODGEBALL_API APowerUpPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpPickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleAnywhere, category = spawn)
		TSubclassOf<class AAdder_DodgeBallCharacter> player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = powerUp, Meta = (DisplayName = "powerupEnum", ExposeOnSpawn = true))
		TEnumAsByte<PowerUp::PowerUpType> currentPowerup;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;

protected:
	UFUNCTION()
		virtual void OnBeginOverlap(AActor* OtherActor);
	
};
