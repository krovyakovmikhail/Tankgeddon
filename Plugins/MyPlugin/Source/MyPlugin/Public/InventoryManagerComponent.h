// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ThirdParty/CryptoPP/5.6.5/include/argnames.h>

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "InventoryWidget.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPLUGIN_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryManagerComponent();



	FInventoryItemInfo* GetItemData(FName ItemID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UInventoryComponent * LocalInventoryComponent;
         
	UPROPERTY(EditAnywhere)
	UDataTable * InventoryItemsData;
	
	UPROPERTY()
	UInventoryWidget * InventoryWidget;
    
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 20;

	UPROPERTY()
	UInventoryWidget * EquipInventoryWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> EquipInventoryWidgetClass;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DroppedTo);

	void inizialize (FName ItemID) const;
	//void Init(UInventoryComponent * InInventoryComponent); lesson 7
	//
	// ++  lesson 8
	void InitLocalInventory(UInventoryComponent* InInventoryComponent); 

	void InitEquipment(UInventoryComponent * InInventoryComponent);

};
	