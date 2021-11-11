// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"
#include "InventoryCellWidget.h"
#include "InventoryComponent.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(TTESTLOG, All,All)


// Sets default values for this component's properties
UInventoryManagerComponent::UInventoryManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryManagerComponent::OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DroppedTo)
{
	if (DraggedFrom == nullptr || DroppedTo == nullptr)
	{
		return;
	}

	UInventoryComponent* FromInventory = DraggedFrom->ParentInventoryWidget->RepresentInventory;
	UInventoryComponent* ToInventory = DroppedTo->ParentInventoryWidget->RepresentInventory;
	
	if (FromInventory == nullptr || ToInventory == nullptr)
	{
		return;;
	}

	FInventorySlotInfo FromSlot = DraggedFrom->GetItem();
	FInventorySlotInfo ToSlot = DroppedTo->GetItem();
	
	if (FromSlot.Count <= 0)
	{
		return;
	}

	FInventoryItemInfo* FromInfo = GetItemData(FromSlot.ID);
	FInventoryItemInfo* ToInfo = GetItemData(ToSlot.ID);

	if (FromInfo == nullptr || (ToSlot.ID != NAME_None && ToInfo == nullptr))
	{
		return;
	}
	
	const int32 MaxCount = ToInventory-> GetMaxItemAmount(DroppedTo->IndexInInventory, *FromInfo);
	if (MaxCount == 0)
	{
		return;
	}
	/*else if (MaxCount < 0)
	{
		//
	}*/
	else if (MaxCount > 0)
	{

		int32 ItemsToAdd = FMath::Min(MaxCount, FromSlot.Count);
		ToSlot.Count = FromSlot.Count - ItemsToAdd;
		ToSlot.ID = FromSlot.ID;
		ToInfo = FromInfo;
		FromSlot.Count = ItemsToAdd;		
	}
	
	FromInventory->SetItem(DraggedFrom->IndexInInventory, ToSlot);
	ToInventory->SetItem(DroppedTo->IndexInInventory, FromSlot);

	
	DraggedFrom->Clear();
	if (ToInfo)
	{
		DraggedFrom->AddItem(ToSlot, *ToInfo);
	}

	DroppedTo->Clear();
	DroppedTo->AddItem(FromSlot, *FromInfo);
	
     
}

void UInventoryManagerComponent::inizialize(FName ItemID) const
{
	FInventoryItemInfo*  ObshyaInfaPredmet = InventoryItemsData->FindRow<FInventoryItemInfo>("Bomb", "");

	if(ObshyaInfaPredmet)
	{
		FInventorySlotInfo Predmet;
		Predmet.ID = ObshyaInfaPredmet->ID;
		Predmet.Count = 12;
		if (LocalInventoryComponent)
		{
			LocalInventoryComponent->SetItem(0, Predmet);
		}
		
	}
}

void UInventoryManagerComponent::InitLocalInventory(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent && InventoryItemsData && InventoryWidgetClass)
	{
		if (InventoryWidget)
		{
			InventoryWidget->RemoveFromViewport();
		}
		LocalInventoryComponent = InInventoryComponent;

		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		
		InventoryWidget->RepresentInventory = LocalInventoryComponent;

		InventoryWidget ->AddToViewport();

		InventoryWidget ->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);

		for (auto& Item : LocalInventoryComponent->GetItems())
		//for (auto& [Index, Slot] : LocalInventoryComponent->GetItems())
		{
			if (FInventoryItemInfo* Data = GetItemData(Item.Value.ID))
			{
				Data->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *Data, Item.Key);
			}
		}
	}

	
}

void UInventoryManagerComponent::InitEquipment(UInventoryComponent* InInventoryComponent)
{
	
		ensure(EquipInventoryWidgetClass);
		EquipInventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), EquipInventoryWidgetClass);
		EquipInventoryWidget->RepresentInventory = InInventoryComponent;
	
	
		EquipInventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);		
		EquipInventoryWidget->AddToViewport();
}


FInventoryItemInfo * UInventoryManagerComponent::GetItemData(FName ItemID)
{
	
	
	
    return InventoryItemsData ? InventoryItemsData->FindRow<FInventoryItemInfo>(ItemID, "") : nullptr;
}












//   lesson 7
/*void UInventoryManagerComponent::Init(UInventoryComponent * InInventoryComponent)
{

	if (InInventoryComponent && InventoryItemsData && InventoryWidgetClass)

	{
		
		if (InventoryWidget)
		{
			InventoryWidget->RemoveFromViewport();
		}

				
		LocalInventoryComponent = InInventoryComponent;
		
		//inizialize("Bomb");
	
		
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);

		InventoryWidget->AddToViewport();			
		
	
		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));		

		
		
		InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);

		for (auto& Item : LocalInventoryComponent->GetItems())
			//for (auto& [Index, Slot] : LocalInventoryComponent->GetItems())
		{
			if (FInventoryItemInfo* Data = GetItemData(Item.Value.ID))
			{
				Data->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *Data, Item.Key);
			}
		}

	
	}
	/*LocalInventoryComponent = InInventoryComponent;

	if (LocalInventoryComponent && InventoryItemsData)
	{
		ensure(InventoryWidgetClass);
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);

		InventoryWidget->AddToViewport();
   	 
		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		for (auto& Item : LocalInventoryComponent->GetItems())
		{
			FInventoryItemInfo* ItemData = GetItemData(Item.Value.ID);
			if (ItemData)
			{
				ItemData->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
			}
		}
	}*/
