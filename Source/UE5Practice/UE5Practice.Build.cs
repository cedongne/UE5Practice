// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5Practice : ModuleRules
{
	public UE5Practice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
