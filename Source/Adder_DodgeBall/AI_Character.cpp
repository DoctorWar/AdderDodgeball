// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "AI_Character.h"


// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AI character should also be able to function as a regular character
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//Set defaults for AI variables
	targetPoint = FVector::ZeroVector;
	AITimer = 0;
	AITimeStep = 1.25;
	targetRegion = nullptr;
	boundsPoint = FVector(0, 0, 0);
	boundsVector = FVector(640, 640, 480);
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	targetPoint = GetTransform().GetLocation();
	if (targetRegion->IsValidLowLevel() && targetRegion != nullptr) {
		targetRegion->GetActorBounds(false, boundsPoint, boundsVector);
		//saves dividing by 2 every frame..
		boundsVector.X *= 0.5;
		boundsVector.Y *= 0.5;
	}
}

// Called every frame
void AAI_Character::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AITimer = AITimer - DeltaTime;
	if (AITimer < 0) {
		targetPoint += FVector(rand() % 511 - 255, rand() % 511 - 255, 0);
		if (targetPoint.X > boundsPoint.X + boundsVector.X) targetPoint.X = boundsPoint.X + boundsVector.X;
		if (targetPoint.X < boundsPoint.X - boundsVector.X) targetPoint.X = boundsPoint.X - boundsVector.X;
		if (targetPoint.Y > boundsPoint.Y + boundsVector.Y) targetPoint.Y = boundsPoint.Y + boundsVector.Y;
		if (targetPoint.Y < boundsPoint.Y - boundsVector.Y) targetPoint.Y = boundsPoint.Y - boundsVector.Y;
		AITimer = AITimer + AITimeStep;
	}
	if (FMath::Abs(FVector::Dist(targetPoint, GetTransform().GetLocation())) > 32) {
		GetMovementComponent()->AddInputVector(targetPoint - GetTransform().GetLocation(), false);
	}
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

