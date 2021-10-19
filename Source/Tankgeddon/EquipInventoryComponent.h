// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "EquipInventoryComponent.generated.h"

class ATankPawn;
/**
 * 
 */
class ATAnkPawn;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGEDDON_API UEquipInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

	public:
	UEquipInventoryComponent();

	protected:
	virtual void BeginPlay() override;

	public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item) override;

	protected:
	UPROPERTY(EditAnywhere)
	TMap<int32, EEquipSlot> EquipSlots;

	public:
	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item) override;

	UPROPERTY()
	ATankPawn* TankPawn;
};
