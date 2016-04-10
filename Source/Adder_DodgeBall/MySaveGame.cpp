// Fill out your copyright notice in the Description page of Project Settings.

#include "Adder_DodgeBall.h"
#include "MySaveGame.h"



UMySaveGame::UMySaveGame()
{
	SaveSlotName = TEXT("SaveSlot");
	UserIndex = 0;
	Score = 0;
}

