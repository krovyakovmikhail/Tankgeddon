// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TExtBlock.h"
#include "QuestDescription.generated.h"


class UObjectiveWidget;

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestDescription : public UUserWidget
{
	GENERATED_BODY()

	public:
	void Init(class AQuests * Quest);

	protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock * NameText;
	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox * ObjectivesList;
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock * DescriptionText;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

};
