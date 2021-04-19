// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleShipGameBlockGrid.h"
#include "BattleShipGameBlock.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ABattleShipGameBlockGrid::ABattleShipGameBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void ABattleShipGameBlockGrid::BeginPlay()
{
	const int32 NumBlocks = Size * Size;

	if (Size < ShipLenght) {
		ShipLenght = Size;
	}
	if (NumBlocks < BattleShips * ShipLenght) {
		BattleShips = 1;
	}

	AShip* currentShipPTR = nullptr;
	bool continueShip = false;
	int32 shipDone = 1;
	int32 line = 1;

	//lists all the blocks that could have a ship in them
	for (int32 i = 0; i < NumBlocks; i++)
	{
		if (i >= (line * Size)) {
			line++;
		}
		if ((line * Size) - ShipLenght >= i)
			shipLocations.Emplace(i);
	}
	//chooses random blocks from previous list that will have a ship in them during this game and makes sure ships longer than 1 block don't overlap
	int32 randomInt;
	for (int32 i = 0; currentShipLocations.Num() < BattleShips; i++) {
		randomInt = FMath::RandRange(0, shipLocations.Num() - 1);
		currentShipLocations.AddUnique(shipLocations[randomInt]);
		shipLocations.Remove(currentShipLocations[i]);
		for (size_t j = 1; j < ShipLenght; j++)
		{
			shipLocations.Remove(currentShipLocations[i] + j);
			shipLocations.Remove(currentShipLocations[i] - (j - 1));
		}
	}
	currentShipLocations.Sort();
	//an extra zero is set to the end of the line just to be sure that the array isn't called out of bounds by accident
	currentShipLocations.Emplace(0);
	line = 1;
	int32 madeShips = 0;
	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex % Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		if (BlockIndex >= (line * Size)) {
			line++;
		}

		// Spawn a block
		ABattleShipGameBlock* NewBlock = GetWorld()->SpawnActor<ABattleShipGameBlock>(BlockLocation, FRotator(0, 0, 0));

		if (continueShip) {
			//if a ship set in previous block is long enough to reach this block, this block will also have that ship
			NewBlock->myShip = currentShipPTR;
			currentShipPTR->blocks.Emplace(NewBlock);
			shipDone++;
			if (ShipLenght <= shipDone) {
				continueShip = false;
				shipDone = 1;
			}
		}
		else if (BlockIndex == currentShipLocations[madeShips]) {
			//a ship will be created and given to this block if a ship should be spawned in this block
			currentShipPTR = GetWorld()->SpawnActor<AShip>(FVector(0, 0, 0), FRotator(0, 0, 0));
			NewBlock->myShip = currentShipPTR;
			currentShipPTR->blocks.Emplace(NewBlock);
			shipArray.Emplace(currentShipPTR);
			madeShips++;
			if(ShipLenght > 1)
				continueShip = true;
		}
		else {
			//the block will not have a ship assigned if the block should not have a ship
			NewBlock->myShip = nullptr;
		}

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}

void ABattleShipGameBlockGrid::AddScore()
{
	//Score is used to track moves used by player
	Score++;
	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Moves used: {0}"), FText::AsNumber(Score)));

	//The game is won if player has found all the ships 
	int blownShips = 0;
	for (int32 Index = 0; Index != shipArray.Num(); ++Index)
	{
		if (shipArray[Index]->isBlown) {
			blownShips++;
		}
	}
	if (blownShips == shipArray.Num()) {
		ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "You won! Moves used: {0}"), FText::AsNumber(Score)));
	}
}

#undef LOCTEXT_NAMESPACE
