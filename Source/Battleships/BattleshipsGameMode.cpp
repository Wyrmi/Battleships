// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleshipsGameMode.h"
#include "BattleshipsPlayerController.h"
#include "BattleshipsPawn.h"

ABattleshipsGameMode::ABattleshipsGameMode()
{
	// no pawn by default
	DefaultPawnClass = ABattleshipsPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ABattleshipsPlayerController::StaticClass();
}
