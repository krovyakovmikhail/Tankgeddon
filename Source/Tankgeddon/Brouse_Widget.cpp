// Fill out your copyright notice in the Description page of Project Settings.


#include "Brouse_Widget.h"

void UBrouse_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BrowseBtn)
	{
		BrowseBtn->OnClicked.AddDynamic(this, &UBrouse_Widget::OnBrowseBtnClicked);
	}
}

void UBrouse_Widget::OnBrowseBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("BrowseBtn Clicked"));
	BrowseBtn->SetVisibility(ESlateVisibility::Hidden);
	
}
