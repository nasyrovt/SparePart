// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SparePart : ModuleRules
{
	public SparePart(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
    }
}
