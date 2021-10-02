// Fill out your copyright notice in the Description page of Project Settings.


#include "SMiniMap.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMiniMap::Construct(const FArguments& InArgs)
{
	PlayerImage = InArgs._PlayerImage;
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SMiniMap::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FVector2D localSize = AllottedGeometry.GetLocalSize();

	FSlateBrush brush;
	brush.SetResourceObject(PlayerImage); // PlayerImage это UTexture2D, его можно передать через аргумент или атрибут

	// –исуем границу уровн€, желательно передавать border через атрибут или аргумент, чтобы их можно было быстро и удобно мен€ть через Ѕѕ

	TArray<FVector2D> border;
	border.Add(localSize * FVector2D(0.f, 0.f));
	border.Add(localSize * FVector2D(0.f, 1.f));
	border.Add(localSize * FVector2D(1.f, 1.f));
	border.Add(localSize * FVector2D(1.f, 0.f));
	border.Add(localSize * FVector2D(0.f, 0.f));

	FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(),border);

	// –исуем преп€тстви€ на карте, поскольку Ѕѕ не поддерживаем вложенные массивы (TArray<TArray<FVector2D>>), а нам нужно задать сразу
	// много преп€дствий, используем массив FBox2D, который содержит в себе 2 FVector

	TArray<FBox2D> obstacles;

	obstacles.Add(FBox2D(localSize * FVector2D(0.2f, 0.3f), localSize * FVector2D(0.3f, 0.3f)));
	obstacles.Add(FBox2D(localSize * FVector2D(0.7f, 0.6f), localSize * FVector2D(0.7f, 0.8f))); 
	obstacles.Add(FBox2D(localSize * FVector2D(0.3f, 0.8f), localSize * FVector2D(0.7f, 0.8f)));

	for (auto& obs : obstacles)
	{
		TArray<FVector2D> points;
		points.Add(obs.Min);
		points.Add(obs.Max);

		FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(),points);
	}


	FSlateDrawElement::MakeBox(OutDrawElements,	LayerId,AllottedGeometry.ToPaintGeometry(localSize * FVector2D(0.5f, 0.5f), brush.ImageSize),&brush);
	FSlateDrawElement::MakeBox(	OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(localSize * FVector2D(0.3f, 0.5f), brush.ImageSize),&brush);
	FSlateDrawElement::MakeBox(	OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(localSize * FVector2D(0.7f, 0.3f), brush.ImageSize),&brush);
	FSlateDrawElement::MakeBox(	OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(localSize * FVector2D(0.8f, 0.2f), brush.ImageSize),&brush);

	return 0;
}