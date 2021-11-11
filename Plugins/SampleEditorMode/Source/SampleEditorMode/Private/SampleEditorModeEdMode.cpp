// Copyright Epic Games, Inc. All Rights Reserved.

#include "SampleEditorModeEdMode.h"
#include "SampleEditorModeEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "Engine/Selection.h"

const FEditorModeID FSampleEditorModeEdMode::EM_SampleEditorModeEdModeId = TEXT("EM_SampleEditorModeEdMode");

FSampleEditorModeEdMode::FSampleEditorModeEdMode()
{

}

FSampleEditorModeEdMode::~FSampleEditorModeEdMode()
{

}

void FSampleEditorModeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FSampleEditorModeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FSampleEditorModeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FSampleEditorModeEdMode::UsesToolkits() const
{
	return true;
}

void FSampleEditorModeEdMode::ActorSelectionChangeNotify()
{
	FEdMode::ActorSelectionChangeNotify();

	UpdateSelectedActors()
}

void FSampleEditorModeEdMode::UpdateSelectedActors()
{
	SelectedActors.Empty();
	USelection* Selection = GEditor->GetSelectedActors();
	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		AActor*SelectorActor = Cast<AActor>(*Iter);
		if (SelectorActor)
		{
			SelectedActors.AddUnique(SelectorActor);
			
		}
	}
}




