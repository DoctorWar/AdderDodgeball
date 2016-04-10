// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ADDER_DODGEBALL_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	FString	SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
		int32 UserIndex;

	UMySaveGame();
	
	
};
