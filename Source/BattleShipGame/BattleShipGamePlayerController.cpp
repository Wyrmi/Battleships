// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleShipGamePlayerController.h"

ABattleShipGamePlayerController::ABattleShipGamePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
