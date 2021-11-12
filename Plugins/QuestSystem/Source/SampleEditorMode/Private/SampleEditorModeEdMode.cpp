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

	UpdateSelectedActors();

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

void FSampleEditorModeEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	for (AActor* BoundedActor : SelectedActors)
	{
		DrawWireBox(
			PDI,
			BoundedActor->GetComponentsBoundingBox(true),
			FColor::Yellow,
			1);
	}

	FEdMode::Render(View, Viewport, PDI);
}

void FSampleEditorModeEdMode::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport,
                                      const FSceneView* View, FCanvas* Canvas)
{
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);

	for (AActor* SelectedActor : SelectedActors)
	{
		if (Canvas)
		{
			FBox Bounds = SelectedActor->GetComponentsBoundingBox(true);

			FVector drawPos = Bounds.GetCenter() + 
					FVector(0.f, 0.f, Bounds.GetExtent().Z);
			FVector2D PixelLocation;
			View->ScreenToPixel(View->WorldToScreen(drawPos), PixelLocation);
			PixelLocation /= ViewportClient->GetDPIScale();
			UFont* RenderFont = GEngine->GetSmallFont();
			Canvas->DrawShadowedText(PixelLocation.X, PixelLocation.Y, 
					FText::FromString(SelectedActor->GetName()), 
					RenderFont, FColor::Yellow);
		}
	}
}

void FSampleEditorModeEdMode::ActorSelectionChangeNotify()
{
	FEdMode::ActorSelectionChangeNotify();

	UpdateSelectedActors();
}

void FSampleEditorModeEdMode::UpdateSelectedActors()
{
	SelectedActors.Empty();
	USelection* Selection = GEditor->GetSelectedActors();
	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		AActor * SelectorActor = Cast<AActor>(*Iter);

		
		if (SelectorActor)
		{
			SelectedActors.AddUnique(SelectorActor);
		}
		
	}
}




