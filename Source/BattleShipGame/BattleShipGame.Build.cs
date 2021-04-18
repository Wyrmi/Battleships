// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BattleShipGame : ModuleRules
{
	public BattleShipGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
