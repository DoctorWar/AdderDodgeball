// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "Adder_DodgeBallCharacter.h"
#include "Ad_CharacterAIComponent.h"


// Sets default values for this component's properties
UAd_CharacterAIComponent::UAd_CharacterAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//Set defaults for AI variables
	targetPoint = FVector::ZeroVector;
	AITimer = 10;
	AITimeStep = 1.25;
	targetRegion = nullptr;
	boundsPoint = FVector(0, 0, 0);
	boundsVector = FVector(640, 640, 480);

	OwningPawn = Cast<APawn>(GetOwner());
	isAI = false;
}


// Called when the game starts
void UAd_CharacterAIComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//reset owningpawn again, probably not needed since it's in the constructor
	OwningPawn = Cast<APawn>(GetOwner());
	PlayersPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	targetPoint = OwningPawn->GetTransform().GetLocation();
	if (targetRegion->IsValidLowLevel() && targetRegion != nullptr) {
		targetRegion->GetActorBounds(false, boundsPoint, boundsVector);
		//saves dividing by 2 every frame..
		//boundsVector.X *= 0.5;
		//boundsVector.Y *= 0.5;
	}

	//turn off AI component's tick function if the player controls this one
	if (OwningPawn == PlayersPawn) {// UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		PrimaryComponentTick.bCanEverTick = false;
		isAI = false;
	} else {
		PrimaryComponentTick.bCanEverTick = true;
		isAI = true;
		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn))
			Cast<AAdder_DodgeBallCharacter>(OwningPawn)->isAI = true;
	}
}


// Called every frame
void UAd_CharacterAIComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (!isAI) return;// OwningPawn == PlayersPawn) return;
	// ...
	AITimer = AITimer - DeltaTime;

	if (AITimer < 0) {
		targetPoint += FVector(rand() % 511 - 255, rand() % 511 - 255, 0);
		//UE_LOG(LogTemp, Warning, TEXT("Iterating"));
		for (TActorIterator<AActor> Tai(GetWorld()); Tai; ++Tai) {
			if (Tai->ActorHasTag("Ball")) {
				//chase the ball if it's on AI side of the court
				FVector BallPoint = Tai->GetActorLocation();
				if (BallPoint.X < boundsPoint.X + boundsVector.X && BallPoint.X > boundsPoint.X - boundsVector.X
					&&BallPoint.Y < boundsPoint.Y + boundsVector.Y && BallPoint.Y > boundsPoint.Y - boundsVector.Y) {
					targetPoint = BallPoint;
				}
				//run from the ball if it's flying
				FVector BallVelocity = Tai->GetVelocity();
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("BallVector: %f"), BallVelocity.Size()));
				if (BallVelocity.Size() > 80.0f) {
					FVector UserPoint = OwningPawn->GetTransform().GetLocation();
					FVector MovePoint = (OwningPawn->GetTransform().GetLocation() - BallPoint);
					MovePoint.Normalize();
					targetPoint = UserPoint + (MovePoint * 180);
				}
			}
		}
		targetPoint.Z = OwningPawn->GetTransform().GetLocation().Z;
		if (targetPoint.X > boundsPoint.X + boundsVector.X) targetPoint.X -= 255;// = boundsPoint.X + boundsVector.X;
		if (targetPoint.X < boundsPoint.X - boundsVector.X) targetPoint.X += 255;// = boundsPoint.X - boundsVector.X;
		if (targetPoint.Y > boundsPoint.Y + boundsVector.Y) targetPoint.Y -= 255;// = boundsPoint.Y + boundsVector.Y;
		if (targetPoint.Y < boundsPoint.Y - boundsVector.Y) targetPoint.Y += 255;// = boundsPoint.Y - boundsVector.Y;
		AITimer = AITimer + AITimeStep;
	}

	if (FMath::Abs(FVector::Dist(targetPoint, OwningPawn->GetTransform().GetLocation())) > 32) {
		//OwningPawn->AddMovementInput(targetPoint - OwningPawn->GetTransform().GetLocation(), 1, false);
		OwningPawn->GetMovementComponent()->AddInputVector(targetPoint - OwningPawn->GetTransform().GetLocation(), false);
	}
}

