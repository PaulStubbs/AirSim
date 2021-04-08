// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Airsim_Drone : ModuleRules
{

	public Airsim_Drone(ReadOnlyTargetRules Target) : base(Target)
	{
		//PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ImageWrapper", "RenderCore", "RHI", "AssetRegistry", "PhysicsCore", "PhysXVehicles", "PhysXVehicleLib", "PhysX", "APEX", "Landscape", "AirSim" });
		PrivateDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore"} );

		//PublicIncludePaths.Add(Path.Combine(AirLibPath, "include"));
		//PublicIncludePaths.Add(Path.Combine(AirLibPath, "deps", "eigen3"));
		AddOSLibDependencies(Target);

		//suppress VC++ proprietary warnings
		PublicDefinitions.Add("_SCL_SECURE_NO_WARNINGS=1");
		PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS=1");
		PublicDefinitions.Add("HMD_MODULE_INCLUDED=0");
	}

	private void AddOSLibDependencies(ReadOnlyTargetRules Target)
	{
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// for SHGetFolderPath.
			PublicAdditionalLibraries.Add("Shell32.lib");

			//for joystick support
			PublicAdditionalLibraries.Add("dinput8.lib");
			PublicAdditionalLibraries.Add("dxguid.lib");
		}

		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			// needed when packaging
			PublicAdditionalLibraries.Add("stdc++");
			PublicAdditionalLibraries.Add("supc++");
		}
	}
}
