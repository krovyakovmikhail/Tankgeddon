// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"

void UStartMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (PlayBtn)
    {
        PlayBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::OnPlayClicked);
    }
    if (OptionsBtn)
    {
        OptionsBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::OnOptionsClicked);
    }
    if (QuitBtn)
    {
        QuitBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::OnQuitClicked);
    }

}

void UStartMenuWidget::OnPlayClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("PLAY"));
    //UGameplayStatics::OpenLevel()
    // первым параметром требуется передать  UObject * WorldContextObject
};
void UStartMenuWidget::OnOptionsClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OPTIONS"));
};
void UStartMenuWidget::OnQuitClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("QUIT"));
};