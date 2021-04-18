// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleShipGameGameMode.h"
#include "BattleShipGamePlayerController.h"
#include "BattleShipGamePawn.h"

ABattleShipGameGameMode::ABattleShipGameGameMode()
{
	// no pawn by default
	DefaultPawnClass = ABattleShipGamePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ABattleShipGamePlayerController::StaticClass();
}
