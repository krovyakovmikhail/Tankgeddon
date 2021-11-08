// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestDescription.h"
#include "ObjectiveWidget.h"
#include "Quests.h"

void UQuestDescription::Init(AQuests* Quest)
{
	if (Quest)
	{
		if (NameText)
		{
			NameText->SetText(Quest->Name);
		}
		if (DescriptionText)
		{
			DescriptionText->SetText(Quest->Description);
		}
		if (ObjectiveWidgetClass && ObjectivesList)
		{
			ObjectivesList->ClearChildren();
			
			for (UObjective* Objective : Quest->GetObjectives())
			{
				UObjectiveWidget * ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
				
				ObjectiveWidget->Init(Objective);
				
				ObjectivesList->AddChild(ObjectiveWidget);
			}
		}
	}

}
