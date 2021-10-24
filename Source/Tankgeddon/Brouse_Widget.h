// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Brouse_Widget.generated.h"

/**
 * 
 */
UCLASS()
class TANKGEDDON_API UBrouse_Widget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* BrowseBtn;

	UPROPERTY(meta = (BindWidgetOptional))
		UImage* BrowseImage;

	

public:
	UFUNCTION()
	void NativeConstruct() override;
	UFUNCTION()
	void OnBrowseBtnClicked();

};
