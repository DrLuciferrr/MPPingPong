// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MPPingPong : ModuleRules
{
	public MPPingPong(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG",

        "OnlineSubsystem",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	
		PublicIncludePaths.AddRange(new string[] { "MPPingPong" } );
    }
}
