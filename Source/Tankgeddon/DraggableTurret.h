// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TExtBlock.h"
#include "DraggableTurret.generated.h"

/**
 * 
 */
UCLASS()
class TANKGEDDON_API UDraggableTurret : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	UPROPERTY(EditAnyWhere)
	FText TurretName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TurretNameText;

protected: 
    FReply NativeOnMouseButtonDown(const FGeometry& InGeometry,
        const FPointerEvent& InMouseEvent) override;
    void NativeOnDragDetected(const FGeometry& InGeometry,
        const FPointerEvent& InMouseEvent,
        UDragDropOperation*& OutOperation) override;
    bool NativeOnDragOver(const FGeometry& InGeometry,
        const FDragDropEvent& InDragDropEvent,
        UDragDropOperation* InOperation) override;
    bool NativeOnDrop(const FGeometry& InGeometry,const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation) override;


    UFUNCTION()
        void OnDragCancelledHandle(UDragDropOperation* Operation);

};
