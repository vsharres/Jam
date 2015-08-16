// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjetoJam : ModuleRules
{
	public ProjetoJam(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.AddRange(new string[] { "ProjetoJam/Public", "ProjetoJam/Private" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
	}
}
