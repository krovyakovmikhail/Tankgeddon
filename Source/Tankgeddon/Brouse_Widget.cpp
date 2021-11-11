// Fill out your copyright notice in the Description page of Project Settings.


#include "Brouse_Widget.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "MediaAssets/Public/FileMediaSource.h"
#include "MediaAssets/Public/MediaSoundComponent.h"


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
	
	//File dialog ++ 
	IDesktopPlatform * Platform = FDesktopPlatformModule::Get();	
	auto * ParentHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
	FString FileTypes = "All Files(*.PNG;*.JPG;*.MP4)|*.PNG;*.JPG;*.MP4|"
					"Image Files(*.PNG;*.JPG;)|*.PNG;*.JPG;|"
					"Video Files(*.MP4)|*.MP4";
	TArray<FString> OutFileNames;
	uint32 SelectionFlag = 0;
		
	if (Platform && ParentHandle)
	{
		Platform->OpenFileDialog(ParentHandle, "Choose content", "", "", FileTypes, SelectionFlag, OutFileNames);
	}
	//File dialog --
	
	//video++
	if (MediaPlayer)
	{
		FString Path;
		
		if (OutFileNames.Num() > 0)
		{
			Path = OutFileNames[0];
		}
		
		if (Path.IsEmpty()) return;
		
		int32 res  = Path.Find("MP4");

		if (res > 0)
		{
			UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
			MediaSource->FilePath = Path;
			MediaPlayer->OpenSource(MediaSource);
			Object = BrowseImage->Brush.GetResourceObject();
			
			
		
			if (Object)
			{

				
				X = Cast<UMaterialExpressionTextureSampleParameter>(Object)->GetHeight();
				Y = Cast<UMaterialExpressionTextureSampleParameter>(Object)->GetWidth();
				Size = {static_cast<float>(X),static_cast<float>(Y)};
				BrowseImage->SetBrushSize(Size);
			}
			
			
			
			BrowseImage->SetVisibility(ESlateVisibility::Visible);
		}
		//video--
		else
		{
			UTexture2D * Texture = UKismetRenderingLibrary::ImportFileAsTexture2D(this, Path);
			if (Texture)
			{
				X = Texture->GetSizeX();
				Y =  Texture->GetSizeY();
				
				Size = {static_cast<float>(X),static_cast<float>(Y)};
				BrowseImage->SetBrushSize(Size);
				BrowseImage->SetBrushFromTexture(Texture);
				BrowseImage->SetVisibility(ESlateVisibility::Visible);
				
			}
			
		}
				
					
	}
	
	
}

void UBrouse_Widget::OnCloseBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("CloseBtn Clicked"));
	
}
