// Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class AkUEPlatform_IOS : AkUEPlatform
{
	public AkUEPlatform_IOS(ReadOnlyTargetRules in_TargetRules, string in_ThirdPartyFolder) : base(in_TargetRules, in_ThirdPartyFolder) {}

	public override string SanitizeLibName(string in_libName)
	{
		return in_libName;
	}

	public override string GetPluginFullPath(string PluginName, string LibPath)
	{
		return Path.Combine(LibPath, "lib" + PluginName + ".a");
	}

	public override bool SupportsAkAutobahn { get { return false; } }
	
	public override bool SupportsCommunication { get { return true; } }

	public override List<string> GetPublicLibraryPaths()
	{
		return new List<string> 
		{
			Path.Combine(ThirdPartyFolder, "iOS", akConfigurationDir + "-iphoneos", "lib")
		};
	}
	
	public override List<string> GetPublicAdditionalLibraries()
	{
		return new List<string> 
		{
			SanitizeLibName("AkAACDecoder")
		};
	}
	
	public override List<string> GetPublicDefinitions()
	{
		return new List<string>();
	}
	
	public override List<string> GetPublicAdditionalFrameworks()
	{
		return new List<string>
		{
			"AudioToolbox",
			"CoreAudio"
		};
	}
}
