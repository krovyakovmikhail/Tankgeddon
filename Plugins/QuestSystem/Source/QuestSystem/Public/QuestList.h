// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestDescription.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "QuestList.generated.h"

class UQuestListEntry;
class UQuestListComponent;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestList : public UUserWidget
{
	GENERATED_BODY()
	

	
	public:
	void Init(UQuestListComponent * QuestList);

	protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox * StoryQuestsList;
	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox * SideQuestsList;
	UPROPERTY(meta = (BindWidgetOptional))
	UQuestDescription * ActiveQuestDescription;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestListEntry> QuestEntryClass;    
	UPROPERTY()
	TMap<AQuests*, UQuestListEntry*> QuestEntries;
		

	void OnActiveQuestChanged(AQuests * ActiveQuest);

};
