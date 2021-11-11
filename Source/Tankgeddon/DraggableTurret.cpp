// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableTurret.h"
#include "TurretDragDropOperation.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UDraggableTurret::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (TurretNameText)
    {
        TurretNameText->SetText(TurretName);
    }
}

    FReply UDraggableTurret::NativeOnMouseButtonDown(const FGeometry & InGeometry,
        const FPointerEvent & InMouseEvent)
    {
        if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
        {
            return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this,
                EKeys::LeftMouseButton).NativeReply;
        }
        return FReply::Handled();
    }

    void UDraggableTurret::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
    {
    
        OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UTurretDragDropOperation::StaticClass());
        if (OutOperation)
        {
            UTurretDragDropOperation* TurretDragDropOperation = Cast<UTurretDragDropOperation>(OutOperation);
            TurretDragDropOperation->TurretName = TurretName;
            TurretDragDropOperation->DefaultDragVisual = this;

            SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.5f));
            SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            TurretDragDropOperation->OnDragCancelled.AddDynamic(this, &UDraggableTurret::OnDragCancelledHandle);

        }
        else
        {
            Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
        }
    }

    void UDraggableTurret::OnDragCancelledHandle(UDragDropOperation* Operation)
    {
        SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
        SetVisibility(ESlateVisibility::Visible);
    }


    bool UDraggableTurret::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
    {
        UVerticalBox *verticalBox = Cast<UVerticalBox>(GetParent());     
        UTurretDragDropOperation *TurretDragDropOperation = Cast<UTurretDragDropOperation>(InOperation);


        if (TurretDragDropOperation && verticalBox
            && this != TurretDragDropOperation->DefaultDragVisual)
        {
            int32 IndexDragged = verticalBox->GetChildIndex(TurretDragDropOperation->DefaultDragVisual);

            if (IndexDragged != -1)
            {
                verticalBox->RemoveChildAt(IndexDragged);


                TArray<UWidget*> VBChildren = verticalBox->GetAllChildren();
                verticalBox->ClearChildren();


                for (int32 Counter = 0; Counter < VBChildren.Num(); Counter++)
                {                

                    if (VBChildren[Counter] == this)
                    {
                        verticalBox->AddChildToVerticalBox(TurretDragDropOperation->DefaultDragVisual);
                    }

                    verticalBox->AddChildToVerticalBox(VBChildren[Counter]);
                }
                return true;
            }
        }
        return false;
    }


    bool UDraggableTurret::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
    {
        if (InOperation)
        {
            InOperation->OnDragCancelled.Broadcast(InOperation);
            return true;
        }

        return false;

    }