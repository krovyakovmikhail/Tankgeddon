// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryCellWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPLUGIN_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	FOnItemDrop OnItemDrop;
	UPROPERTY()
	UInventoryComponent* RepresentInventory;

	virtual void NativeConstruct() override;

	void Init(int32 ItemsNum);
	bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo, int32 SlotPosition = -1);

	
protected:

	UPROPERTY(meta = (BindWidgetOptional))
	UUniformGridPanel* ItemCellsGrid;

	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInPow = 5;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;
	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCellWidget*> CellWidgets;
	UPROPERTY(meta = (BindWidgetOptional))
	UInventoryCellWidget* GoldCell;

	UInventoryCellWidget * CreateCellWidget();
	

  
    void OnItemDropped(UInventoryCellWidget * DraggedFrom, UInventoryCellWidget * DroppedTo);
	void InitCellWidget(UInventoryCellWidget* Widget);
};
