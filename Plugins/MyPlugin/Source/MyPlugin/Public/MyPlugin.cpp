// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlugin.h"
#include "MyPluginEdMode.h"

#define LOCTEXT_NAMESPACE "FMyPluginModule"

void FMyPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FMyPluginEdMode>(FMyPluginEdMode::EM_MyPluginEdModeId, LOCTEXT("MyPluginEdModeName", "MyPluginEdMode"), FSlateIcon(), true);
}

void FMyPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FMyPluginEdMode::EM_MyPluginEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPluginModule, MyPlugin)