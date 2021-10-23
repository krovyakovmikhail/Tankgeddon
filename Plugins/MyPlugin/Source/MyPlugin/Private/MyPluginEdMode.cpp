// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPluginEdMode.h"
#include "MyPluginEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FMyPluginEdMode::EM_MyPluginEdModeId = TEXT("EM_MyPluginEdMode");

FMyPluginEdMode::FMyPluginEdMode()
{

}

FMyPluginEdMode::~FMyPluginEdMode()
{

}

void FMyPluginEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FMyPluginEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FMyPluginEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FMyPluginEdMode::UsesToolkits() const
{
	return true;
}




