// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BatteryCollector : ModuleRules
{
	//NOTE: Edited due to conversion from 4.15 to 4.19
	//public BatteryCollector(TargetInfo Target)
	public BatteryCollector(ReadOnlyTargetRules Target) : base (Target)
	{
        //NOTE: UMG is for HUD creation
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
