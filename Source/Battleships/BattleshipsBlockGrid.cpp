// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleshipsBlockGrid.h"
#include "BattleshipsBlock.h"
#include "Ship.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"


#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ABattleshipsBlockGrid::ABattleshipsBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Moves used: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void ABattleshipsBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	AShip* currentShipPTR;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		

		// Spawn a block
		ABattleshipsBlock* NewBlock = GetWorld()->SpawnActor<ABattleshipsBlock>(BlockLocation, FRotator(0,0,0));
		if (BattleShips > 0) {
			currentShipPTR = GetWorld()->SpawnActor<AShip>(FVector(0, 0, 0), FRotator(0, 0, 0));
			NewBlock->myShip = currentShipPTR;
			shipArray.Emplace(currentShipPTR);
			BattleShips--;
		}
		else {
			NewBlock->myShip = nullptr;
		}

		

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}


void ABattleshipsBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Moves used: {0}"), FText::AsNumber(Score)));

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
