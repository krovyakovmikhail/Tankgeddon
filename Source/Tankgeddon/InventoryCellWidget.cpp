// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCellWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventoryDragDropOperation.h"

bool UInventoryCellWidget::AddItem(const FInventorySlotInfo& Item, 
	const FInventoryItemInfo& ItemInfo)
{
	if (bHasItem)
	{
		return false;
	}

	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(ItemInfo.Icon.Get());
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (CountText)
	{
		CountText->SetText(FText::FromString(FString::FromInt(Item.Count)));
	}	CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	bHasItem = true;
	StoredItem = Item;

	return true;
}

void UInventoryCellWidget::Clear()
{
	if (ItemImage)
	{
		ItemImage->SetBrush(FSlateBrush());
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}

	if (CountText)
	{
		CountText->SetText(FText::FromString("0"));
		CountText->SetVisibility(ESlateVisibility::Hidden);
	}

	bHasItem = false;
	StoredItem = FInventorySlotInfo();
}

const FInventorySlotInfo& UInventoryCellWidget::GetItem() const
{
	return StoredItem;
}

FReply UInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsDraggable && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Handled();

}

void UInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UInventoryDragDropOperation::StaticClass());
	if (OutOperation) 
	{
		/*UInventoryDragDropOperation* InventoryDragDropOperation = Cast<UInventoryDragDropOperation>(OutOperation);
		
		InventoryDragDropOperation->SourceCell = this;
		InventoryDragDropOperation->DefaultDragVisual = this;*/
		OutOperation->DefaultDragVisual = this;
	}
	else 
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}

}

bool UInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventoryCellWidget* OtherCell = InOperation ? Cast<UInventoryCellWidget>(InOperation->DefaultDragVisual) : nullptr;
	if (OtherCell && OtherCell != this)
	{
		OnItemDrop.Broadcast(OtherCell, this);
		return true;
	}

	return false;

	/*UInventoryDragDropOperation* InventoryDragDropOperation = Cast<UInventoryDragDropOperation>(InOperation);
	if (InventoryDragDropOperation && InventoryDragDropOperation->SourceCell != this)
	{
		if (OnItemDrop.IsBound())
		{
			OnItemDrop.Broadcast(InventoryDragDropOperation->SourceCell, this);
		}
	}

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	*/
}

/////////////////


