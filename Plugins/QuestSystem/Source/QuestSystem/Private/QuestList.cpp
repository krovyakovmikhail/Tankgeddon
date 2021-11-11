// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestList.h"

#include "QuestListComponent.h"
#include "QuestListEntry.h"
#include "Quests.h"

void UQuestList::Init(UQuestListComponent* QuestList)
{
	if (QuestList && QuestEntryClass)
	{
		for (AQuests* Quest : QuestList->GetQuests())
		{
			UScrollBox * Scroll = Quest->IsStoryQuest() ? StoryQuestsList : SideQuestsList;
			if (Scroll)
			{
				UQuestListEntry * QuestEntry = 
							CreateWidget<UQuestListEntry>(this, QuestEntryClass);
				QuestEntry->SetQuestText(Quest->Name);
				QuestEntry->OnQuestChosen.BindUObject(QuestList, 
							&UQuestListComponent::SetActiveQuest, Quest);
				QuestEntries.Add(Quest, QuestEntry);
				Scroll->AddChild(QuestEntry);
			}
		}
		OnActiveQuestChanged(QuestList->GetActiveQuest());
		QuestList->OnActiveQuestChanged.AddUObject(this, &UQuestList::OnActiveQuestChanged);
	}
}

void UQuestList::OnActiveQuestChanged(AQuests* ActiveQuest)
{
	for (const TPair<AQuests*, UQuestListEntry*>& Pair : QuestEntries)
	{
		Pair.Value->SetIsSelected(Pair.Key == ActiveQuest);
	}
	if (ActiveQuestDescription)
	{
		ActiveQuestDescription->Init(ActiveQuest);
		ActiveQuestDescription->SetVisibility(ActiveQuest ? 
			ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}

}
	

