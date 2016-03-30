// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Adder_DodgeBall.h"
#include "Engine.h" 
#include "Adder_DodgeBallCharacter.h"

AAdder_DodgeBallCharacter::AAdder_DodgeBallCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Attach AI script...
	AIComponent = CreateDefaultSubobject<UAd_CharacterAIComponent>(TEXT("AIScript"));

	////// Create a camera boom...
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->AttachTo(RootComponent);
	//CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	//CameraBoom->TargetArmLength = 100.f;
	//CameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	////// Create a camera...
	//TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	//TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	//TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	isAI = false;
	teamNumber = -1;
	isAlive = true;
	downTime = 0.0f;
	ballRef = nullptr;
}


void AAdder_DodgeBallCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("BeginPlay"));
	for (TActorIterator<ACamera> Tai(GetWorld()); Tai; ++Tai)
	{
		if (Tai->ActorHasTag("StaticCamera"))
		{
			UE_LOG(LogTemp, Error, TEXT("CAMERA IS FOUND"));
			StaticCamera = Cast<ACamera>(*Tai);
		}
	}

}

void AAdder_DodgeBallCharacter::WindUp()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("windUp")));
	isThrowing = true;
	if(throwPower >= 1.0f) throwPower = 1.0f;
		else throwPower += 0.16f;
}

void AAdder_DodgeBallCharacter::ThrowBall()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("throw")));
	isThrowing = false;
	if (ballRef != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("launch")));
		ballRef->OwningActor = this;
		ballRef->LaunchBall();
	} else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("nullBall")));
}
