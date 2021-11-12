// Copyright Epic Games, Inc. All Rights Reserved.

#include "SampleEditorMode.h"
#include "SampleEditorModeEdMode.h"

#define LOCTEXT_NAMESPACE "FSampleEditorModeModule"

void FSampleEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FSampleEditorModeEdMode>(FSampleEditorModeEdMode::EM_SampleEditorModeEdModeId, LOCTEXT("SampleEditorModeEdModeName", "SampleEditorModeEdMode"), FSlateIcon(), true);
}

void FSampleEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FSampleEditorModeEdMode::EM_SampleEditorModeEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSampleEditorModeModule, SampleEditorMode)