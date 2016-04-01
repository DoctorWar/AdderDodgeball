// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "MyBallClass.h"
#include "EngineUtils.h"
#include "Adder_DodgeBallCharacter.h"


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
	if (homing)
	{
		homingBallfunc();
		homingDuration += DeltaTime;
	}

}

void AMyBallClass::homingBallfunc()
{
	AAdder_DodgeBallCharacter* currentTarget;
	FVector currentLocation = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z);
	FVector direction(0, 0, 0);
	float distance = 5000;
	for (TActorIterator <AAdder_DodgeBallCharacter> itr(GetWorld()); itr; ++itr)
	{
		if ((itr->GetActorLocation() - this->GetActorLocation()).Size() < distance)
		{
			if (teamNumber != itr->teamNumber)
			{
				currentTarget = *itr;
				direction = (currentTarget->GetActorLocation() - this->GetActorLocation()).GetSafeNormal();
			}
		}
	}
	
	this->SetActorLocation(currentLocation + (direction * 15), false, NULL, ETeleportType::TeleportPhysics);
	if (homingDuration > 1000)
		ResetStats();
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
	case PowerUp::PowerUpType::homing:
		homing = true;
		homingDuration = 0;
	}
}
void AMyBallClass::ResetStats()
{
	Strength = 1;
	Pricision = 5;
	homing = false;
	homingDuration = 0;
}

bool AMyBallClass::GetIsDeadly() {
	return deadly;
}

//BP events don't have C++ code it seems
//void AMyBallClass::LaunchBall(){}


