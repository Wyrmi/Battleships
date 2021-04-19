// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleShipGameBlock.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

UCLASS()
class BATTLESHIPGAME_API AShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//all the blocks that the ship occupies in the grid
	UPROPERTY()
	TArray <class ABattleShipGameBlock*> blocks;
	//has the player found the ship yet?
	UPROPERTY(Category = Ship, EditAnywhere, BlueprintReadOnly)
	bool isBlown;
	//what is done when the player finds the ship
	UFUNCTION()
	void BlowShip();
};
