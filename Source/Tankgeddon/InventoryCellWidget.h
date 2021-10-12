// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TExtBlock.h"
#include "InventoryCellWidget.generated.h"

/**
 * 
 */
class UInventoryCellWidget;
class UInventoryWidget;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellWidget* /*from*/, UInventoryCellWidget* /*to*/);

UCLASS()
class TANKGEDDON_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()

	public:

	FOnItemDrop OnItemDrop;

	bool HasItem() { return bHasItem; }

	bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo);

	void Clear();

	const FInventorySlotInfo& GetItem() const;

	int32 IndexInInventory = -1;
    
	protected:
  
	bool bHasItem;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* ItemImage;
    
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* CountText;

	UPROPERTY()
	FInventorySlotInfo StoredItem;

protected:
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditDefaultsOnly)
		bool bIsDraggable = true;

public:

	UPROPERTY()
		UInventoryWidget* ParentInventoryWidget;

};
