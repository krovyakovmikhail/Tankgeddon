// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKGEDDON_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
    UPROPERTY(meta = (BindWidgetOptional))
        UButton* PlayBtn;
    UPROPERTY(meta = (BindWidgetOptional))
        UButton* OptionsBtn;
    UPROPERTY(meta = (BindWidgetOptional))
        UButton* QuitBtn;

    UFUNCTION()
        void OnPlayClicked();
    UFUNCTION()
        void OnOptionsClicked();
    UFUNCTION()
        void OnQuitClicked();

public:
    void NativeConstruct() override;


  

        

};
