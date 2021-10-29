// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "Brouse_Widget.generated.h"
/**
 * 
 */
UCLASS()
class TANKGEDDON_API UBrouse_Widget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget, BlueprinReadWrite))
		UButton* BrowseBtn;

	UPROPERTY(meta = (BindWidget, BlueprinReadWrite))
		UImage* BrowseImage;

	int32 X = 0;
	int32 Y = 0;
	FVector2D Size = {0,0};
	UObject * Object;	

	UPROPERTY(EditAnywhere)
	UMediaPlayer * MediaPlayer;
	
	UPROPERTY(EditAnywhere)
	UMediaSoundComponent *Sound;

public:
	UFUNCTION()
	void NativeConstruct() override;
	UFUNCTION()
	void OnBrowseBtnClicked();
	UFUNCTION()
		void OnCloseBtnClicked();
};
