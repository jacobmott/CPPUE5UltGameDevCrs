// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPPUE5UltGameDevCrs : ModuleRules
{
	public CPPUE5UltGameDevCrs(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
