// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleShipGameBlock.h"
#include "BattleShipGameBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ABattleShipGameBlock::ABattleShipGameBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
			, RedMaterial(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ABattleShipGameBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ABattleShipGameBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	RedMaterial = ConstructorStatics.RedMaterial.Get();
}

//called when a ship that occupies this block is blown
//sets material to red and makes the block unclickable
void ABattleShipGameBlock::BlowBlock()
{
	BlockMesh->SetMaterial(0, RedMaterial);
	bIsActive = true;
}

void ABattleShipGameBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ABattleShipGameBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ABattleShipGameBlock::HandleClicked()
{
	// Check we are not already active
	if (!bIsActive)
	{
		bIsActive = true;

		// Change material
		//if this block has a ship, that ship is blown up
		if (myShip != nullptr) {
			myShip->BlowShip();
		}
		else {
			BlockMesh->SetMaterial(0, OrangeMaterial);
		}

		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->AddScore();
		}
	}
}

void ABattleShipGameBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}
