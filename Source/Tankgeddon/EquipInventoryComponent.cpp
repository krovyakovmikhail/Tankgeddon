// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipInventoryComponent.h"

#include "TankPawn.h"
#include "Windows/LiveCodingServer/Public/ILiveCodingServer.h"


UEquipInventoryComponent::UEquipInventoryComponent()
{

	EquipSlots.Add(0, EEquipSlot::ES_Muzzle);
	EquipSlots.Add(1, EEquipSlot::ES_LeftCaterpillar);
	EquipSlots.Add(2, EEquipSlot::ES_RightCaterpillar);
	EquipSlots.Add(3, EEquipSlot::ES_Turret);
	EquipSlots.Add(4, EEquipSlot::ES_Bombs);
}

void UEquipInventoryComponent::BeginPlay()
{
	Super:: BeginPlay();
	TankPawn = Cast<ATankPawn>(GetOwner());
	
}
void UEquipInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item)
{
	FInventorySlotInfo* InfoPtr = Items.Find(SlotIndex);
	if (InfoPtr != nullptr ||
		Item.Type != EItemType::IT_Equipment ||
		!EquipSlots.Contains(SlotIndex) ||
		EquipSlots.FindChecked(SlotIndex) != Item.EquipSlot)
	{

		return 0;
	}
	
	return 1;
}

void UEquipInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	FInventorySlotInfo * Equip = GetItem(SlotIndex);
	EEquipSlot EquipSlot = EquipSlots.Contains(SlotIndex) ? EquipSlots.FindChecked(SlotIndex) : EEquipSlot::ES_None;

	if(Equip && TankPawn)
	{

		TankPawn->UnequipItem(EquipSlot, Equip->ID);
	}
	Super::SetItem(SlotIndex, Item);

	if (TankPawn)
	{
		TankPawn->EquipItem(EquipSlot, Item.ID);
	}
}
