// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "MyBallClass.h"


// Sets default values
AMyBallClass::AMyBallClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AMyBallClass::BeginPlay()
{
	Super::BeginPlay();
	ResetStats();
	//SetPowerUp(PowerUp::PowerUpType::strength);
	
}

// Called every frame
void AMyBallClass::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
void AMyBallClass::SetPowerUp(PowerUp::PowerUpType thisPowerUp)
{
	currentPowerup = thisPowerUp;
	ResetStats();
	switch (currentPowerup)
	{
	case PowerUp::PowerUpType::strength:
		Strength = 5;
		break;
	case PowerUp::PowerUpType::precision:
		Pricision = 0;
		break;
	}
}
void AMyBallClass::ResetStats()
{
	Strength = 1;
	Pricision = 5;
}
//BP events don't have C++ code it seems
//void AMyBallClass::LaunchBall(){}


