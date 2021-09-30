// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/NativeWidgetHost.h"
#include "MiniMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKGEDDON_API UMiniMapWidget : public UUserWidget
{
	GENERATED_BODY()

		UPROPERTY(meta = (BindWidgetOptional))
		UNativeWidgetHost* MiniMap;
public:

	void NativeConstruct() override;

};
