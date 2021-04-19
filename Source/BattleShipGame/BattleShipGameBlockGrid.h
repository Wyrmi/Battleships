// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ship.h"
#include "GameFramework/Actor.h"
#include "BattleShipGameBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class ABattleShipGameBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

public:
	ABattleShipGameBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	/** Number of ships in grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 BattleShips;

	/** Lenght of ships in grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 ShipLenght;

	/** Pointer array containing all of ships in grid */
	UPROPERTY()
	TArray <class AShip*> shipArray;

	/** indexes of the blocks where a ship can spawn*/
	UPROPERTY()
	TArray <int32> shipLocations;

	/** indexes of the blocks where a ship will spawn*/
	UPROPERTY()
	TArray <int32> currentShipLocations;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	void AddScore();

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};



