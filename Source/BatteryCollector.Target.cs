// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BatteryCollectorTarget : TargetRules
{
	//NOTE: Edited due to conversion from 4.15 to 4.19
	//public BatteryCollectorTarget(TargetInfo Target)
	public BatteryCollectorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		//NOTE: Edited due to conversion from 4.15 to 4.19		
		ExtraModuleNames.Add("BatteryCollector");
	}

	//
	// TargetRules interface.
	//

	//NOTE: Edited due to conversion from 4.15 to 4.19
	//public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
	//	OutExtraModuleNames.Add("BatteryCollector");
	//}
}
