// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Adder_DodgeBall.h"
#include "Adder_DodgeBallGameMode.h"
#include "Adder_DodgeBallPlayerController.h"
#include "Adder_DodgeBallCharacter.h"

AAdder_DodgeBallGameMode::AAdder_DodgeBallGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAdder_DodgeBallPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}