// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniMapWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MYPLUGIN_API SMiniMap : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMiniMap) :_PlayerImage()
	{}
	
	SLATE_ARGUMENT(UTexture2D*, PlayerImage)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:

	UTexture2D* PlayerImage;
	
};
