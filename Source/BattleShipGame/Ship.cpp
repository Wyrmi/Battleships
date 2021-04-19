// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"

// Sets default values
AShip::AShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isBlown = false;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//called when a block that the ship is on is clicked
//sets isBlown to true and tells all the blocks that the ship is on that their ship has been found
void AShip::BlowShip()
{
	isBlown = true;
	if (blocks.Num() != 0) {
		for (int32 Index = 0; Index != blocks.Num(); ++Index)
		{
			blocks[Index]->BlowBlock();
		}
	}
}

