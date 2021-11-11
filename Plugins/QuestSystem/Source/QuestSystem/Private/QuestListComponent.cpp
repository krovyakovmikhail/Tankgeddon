// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestListComponent.h"
#include "CurrentObjectives.h"
#include "Quests.h"

class CurrentObjectivesWidget;

// Sets default values for this component's properties
UQuestListComponent::UQuestListComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UQuestListComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentObjectivesWidget)
	{
		auto * ObjectivesWidget = CreateWidget<UCurrentObjectives>(GetWorld(), CurrentObjectivesWidget);
		OnActiveQuestChanged.AddUObject(ObjectivesWidget, &UCurrentObjectives::SetCurrentObjectives);
		ObjectivesWidget->AddToViewport();
	}
	
}


// Called every frame
void UQuestListComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestListComponent::AddQuest(AQuests* Quest)
{

	if (ActiveQuest == nullptr || ActiveQuest->IsComplited())
	{
		ActiveQuest = Quest;
		OnActiveQuestChanged.Broadcast(ActiveQuest);
	}
	if (Quest)
	{
		AcceptedQuests.AddUnique(Quest);
		Quest->TakeQuest(GetOwner());
		Quest->OnQuestStatusUpdated.AddLambda([this](AQuests * ChQuest)
		{
			if (ActiveQuest == ChQuest)
			{
				if (OnActiveQuestChanged.IsBound())
				{
					OnActiveQuestChanged.Broadcast(ChQuest);
				}
			}
		});
	}
		
}

const TArray<AQuests*>& UQuestListComponent::GetQuests()
{
	return AcceptedQuests;

}

AQuests* UQuestListComponent::GetActiveQuest() const
{
	return ActiveQuest;
}

void UQuestListComponent::SetActiveQuest(AQuests* Quest)
{
	if (AcceptedQuests.Contains(Quest))
	{
		ActiveQuest = Quest;
		if (OnActiveQuestChanged.IsBound())
		{
			OnActiveQuestChanged.Broadcast(Quest);
		}
	}

}



