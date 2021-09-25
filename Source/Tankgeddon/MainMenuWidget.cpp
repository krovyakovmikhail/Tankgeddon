// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (PlayBtn)
    {
        PlayBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
    }
    if (OptionsBtn)
    {
        OptionsBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsClicked);
    }
    if (QuitBtn)
    {
        QuitBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
    }

}

void UMainMenuWidget::OnPlayClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("PLAY"));
    //UGameplayStatics::OpenLevel()
    // первым параметром требуется передать  UObject * WorldContextObject
};
void UMainMenuWidget::OnOptionsClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OPTIONS"));
};
void UMainMenuWidget::OnQuitClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("QUIT"));
};

