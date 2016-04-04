// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "Adder_DodgeBallCharacter.h"
#include "Engine.h" 
#include "PowerUpPickUp.h"
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
	AITimer = 0.5;
	AITimeStep = 0.75;
	targetRegion = nullptr;
	boundsPoint = FVector(0, 0, 0);
	boundsVector = FVector(640, 640, 480);

	OwningPawn = Cast<APawn>(GetOwner());
	//isAI = false;
	if (Cast<AAdder_DodgeBallCharacter>(OwningPawn))
		Cast<AAdder_DodgeBallCharacter>(OwningPawn)->isAI = false;
	targetActor = nullptr;
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
		PrimaryComponentTick.bCanEverTick = true;// false;
		//isAI = false;
		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn))
			Cast<AAdder_DodgeBallCharacter>(OwningPawn)->isAI = false;
	} else {
		PrimaryComponentTick.bCanEverTick = true;
		//isAI = true;
		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn))
			Cast<AAdder_DodgeBallCharacter>(OwningPawn)->isAI = true;
	}
}


// Called every frame
void UAd_CharacterAIComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//if (!isAI) return;// OwningPawn == PlayersPawn) return;
	if (!Cast<AAdder_DodgeBallCharacter>(OwningPawn)->isAI) return;
	// ...
	AITimer = AITimer - DeltaTime;
	
	if (AITimer < 0) {
		if (!Cast<AAdder_DodgeBallCharacter>(OwningPawn)->isAlive && Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall) {
			Cast<AAdder_DodgeBallCharacter>(OwningPawn)->ThrowBall();
			Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall = false;
			return;
		}
		targetPoint += FVector(rand() % 511 - 255, rand() % 511 - 255, 0);
		//UE_LOG(LogTemp, Warning, TEXT("Iterating"));
		bool gettingPowerUp = false;
		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)->currentPowerup == PowerUp::PowerUpType::none)
		{
			for (TActorIterator<APowerUpPickUp> Tai(GetWorld()); Tai; ++Tai) {
				if (IsClosestToTarget(*Tai)) {
					FVector PUpPoint = Tai->GetActorLocation();
					if (PUpPoint.X < boundsPoint.X + boundsVector.X && PUpPoint.X > boundsPoint.X - boundsVector.X
						&&PUpPoint.Y < boundsPoint.Y + boundsVector.Y && PUpPoint.Y > boundsPoint.Y - boundsVector.Y) {
						targetPoint = PUpPoint;
						gettingPowerUp = true;
					}
				}
			}
		}
		targetActor = nullptr;
		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall || !gettingPowerUp) {
			
			FVector UserPoint = OwningPawn->GetTransform().GetLocation();
			for (TActorIterator<AMyBallClass> Tai(GetWorld()); Tai; ++Tai) {
				if (Tai->ActorHasTag("Ball"))
				{
					if (Tai->GetAttachParentActor() == GetOwner()) {// || Tai->OwningActor == GetOwner()) {
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("BallOwner")));
						targetActor = GetClosestTarget();
						if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)) {
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("hasBall")));
							Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall = true;
							Cast<AAdder_DodgeBallCharacter>(OwningPawn)->ballRef = *Tai;
							if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)->throwPower > 0.75f) {
								Cast<AAdder_DodgeBallCharacter>(OwningPawn)->ThrowBall();
								Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall = false;
							}
						}
						if (targetActor != nullptr) {
							targetPoint = targetActor->GetActorLocation();
						} else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("nullTarget")));
					} else {
						//targetActor = nullptr;
						if (IsClosestToTarget(*Tai)) {
							//chase the ball if it's on AI side of the court
							FVector BallPoint = Tai->GetActorLocation();
							if (BallPoint.X < boundsPoint.X + boundsVector.X && BallPoint.X > boundsPoint.X - boundsVector.X
								&&BallPoint.Y < boundsPoint.Y + boundsVector.Y && BallPoint.Y > boundsPoint.Y - boundsVector.Y) {
								//targetPoint = BallPoint;
								targetPoint = BallPoint + Tai->GetVelocity()* FVector::Dist(BallPoint, UserPoint) * 0.003f;
							}
							//run from the ball if it's flying
							FVector BallVelocity = Tai->GetVelocity();
							bool IsDeadly = Cast<AMyBallClass>(*Tai)->GetIsDeadly();
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("BallVector: %f"), BallVelocity.Size()));
							if (BallVelocity.Size() > 120.0f && IsDeadly) {
								FVector MovePoint = (OwningPawn->GetTransform().GetLocation() - BallPoint);
								MovePoint.Normalize();
								targetPoint = UserPoint + (MovePoint * 180);
							}
						}
					}
				}
			}
		}
		if (targetPoint.X > boundsPoint.X + boundsVector.X) targetPoint.X -= 255;// = boundsPoint.X + boundsVector.X;
		if (targetPoint.X < boundsPoint.X - boundsVector.X) targetPoint.X += 255;// = boundsPoint.X - boundsVector.X;
		if (targetPoint.Y > boundsPoint.Y + boundsVector.Y) targetPoint.Y -= 255;// = boundsPoint.Y + boundsVector.Y;
		if (targetPoint.Y < boundsPoint.Y - boundsVector.Y) targetPoint.Y += 255;// = boundsPoint.Y - boundsVector.Y;
		if(Cast<AAdder_DodgeBallCharacter>(OwningPawn))
		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall == true && targetActor != nullptr) {
			targetPoint = targetActor->GetActorLocation();
		}
		targetPoint.Z = OwningPawn->GetTransform().GetLocation().Z;
		AITimer = AITimer + AITimeStep + (rand() % 100) / 250.0f;
	}
	if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)) {
		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall) {
			if (targetActor == nullptr) {
				targetActor = GetClosestTarget();
				if (targetActor != nullptr) targetPoint = targetActor->GetActorLocation();
			}
	//		if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)) {
				Cast<AAdder_DodgeBallCharacter>(OwningPawn)->WindUp();
	//			if (Cast<AAdder_DodgeBallCharacter>(OwningPawn)->throwPower > 0.95f) {
	//				Cast<AAdder_DodgeBallCharacter>(OwningPawn)->ThrowBall();
	//				Cast<AAdder_DodgeBallCharacter>(OwningPawn)->hasBall = false;
	//			}
	//		}
		}// else if (targetActor != nullptr) { }
	}
	if (FMath::Abs(FVector::Dist(targetPoint, OwningPawn->GetTransform().GetLocation())) > 32) {
		//OwningPawn->AddMovementInput(targetPoint - OwningPawn->GetTransform().GetLocation(), 1, false);
		OwningPawn->GetMovementComponent()->AddInputVector(targetPoint - OwningPawn->GetTransform().GetLocation(), false);
	}
}

bool UAd_CharacterAIComponent::IsClosestToTarget(AActor * inTarget)
{
	FVector targetPos = inTarget->GetActorLocation();
	float actorDist = FVector::Dist(GetOwner()->GetActorLocation(), targetPos);
	int teamNumber = Cast<AAdder_DodgeBallCharacter>(OwningPawn)->teamNumber;
	//iterate through all actors and find teammates... this shouldn't really be done so frequently
	for (TActorIterator<AAdder_DodgeBallCharacter> Cai(GetWorld()); Cai; ++Cai) {
		if (*Cai == GetOwner()) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Found self: %f"), FVector::Dist(GetOwner()->GetActorLocation(), targetPos)));
			continue;
		}
		if (!Cai->isAlive) continue;
		if (Cai->isAI && Cai->teamNumber == teamNumber) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Char Dist: %f"), FVector::Dist(GetOwner()->GetActorLocation(), targetPos)));
			if (FVector::Dist(Cai->GetActorLocation(), targetPos) < actorDist) {
				return false;
			}
		}
	}
	return true;
}

AActor * UAd_CharacterAIComponent::GetClosestTarget()
{
	AActor* targeted = nullptr;
	FVector thisPos = GetOwner()->GetActorLocation();
	float actorDist = 32767.0f;// FVector::Dist(GetOwner()->GetActorLocation(), targetPos);
	int teamNumber = Cast<AAdder_DodgeBallCharacter>(OwningPawn)->teamNumber;
	//iterate through all actors and find teammates... this shouldn't really be done so frequently
	for (TActorIterator<AAdder_DodgeBallCharacter> Cai(GetWorld()); Cai; ++Cai) {
		if (*Cai == GetOwner()) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Found self: %f"), FVector::Dist(GetOwner()->GetActorLocation(), targetPos)));
			continue;
		}
		if (!Cai->isAlive) continue;
		//(Cai->teamNumber == -1 && !Cai->isAI) is a fallback in case team numbers aren't set, will target player only
		if (Cai->teamNumber != teamNumber || (Cai->teamNumber == -1 && !Cai->isAI)) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("AI Tgt Dist: %f"), FVector::Dist(Cai->GetActorLocation(), thisPos)));
			if (FVector::Dist(Cai->GetActorLocation(), thisPos) < actorDist) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("AI Tgt Dist: %f"), FVector::Dist(Cai->GetActorLocation(), thisPos)));
				targeted = *Cai;
			}
		}
	}
	return targeted;
	return nullptr;
}
