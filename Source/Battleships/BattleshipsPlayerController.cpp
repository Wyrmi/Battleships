// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleshipsPlayerController.h"

ABattleshipsPlayerController::ABattleshipsPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
