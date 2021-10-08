// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"
#include "InventoryManagerComponent.h"

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

	// ...
	
}


// Called every frame
void UInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


FInventoryItemInfo * UInventoryManagerComponent::GetItemData(FName ItemID)
{
    return InventoryItemsData ? InventoryItemsData->FindRow<FInventoryItemInfo>(ItemID, "") : nullptr;
}


void UInventoryManagerComponent::Init(UInventoryComponent * InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;

	if (LocalInventoryComponent && InventoryItemsData)
	{
		ensure(InventoryWidgetClass);
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), 
			InventoryWidgetClass);
		InventoryWidget->AddToViewport();
   	 
		InventoryWidget->Init(
			FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		for (auto& Item : LocalInventoryComponent->GetItems())
		{
			FInventoryItemInfo* ItemData = GetItemData(Item.Value.ID);
			if (ItemData)
			{
				ItemData->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
			}
		}
	}
}
