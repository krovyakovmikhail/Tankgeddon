// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests.h"

#include "Objective.h"

// Sets default values
AQuests::AQuests()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuests::BeginPlay()
{
	Super::BeginPlay();
	
}

void AQuests::OnObjectiveCompleted(UObjective* Objective)
{
	if (bKeepObjectivesOrder)
	{
		int32 ObjectiveIndex;
		if (Objectives.Find(Objective, ObjectiveIndex) && 
			Objectives.IsValidIndex(ObjectiveIndex + 1))
		{
			Objectives[ObjectiveIndex + 1]->bCanBeCompleted = true;
		}
	}

	if (OnQuestStatusUpdated.IsBound())
	{
		OnQuestStatusUpdated.Broadcast(this);
	}

}

// Called every frame
void AQuests::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuests::TakeQuest(AActor* Pawn)
{
	if (bIsTaken)
	{
		return;
	}
	
	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		if (Objectives[i])
		{
			Objectives[i]->ActivateObjective(Pawn);
			Objectives[i]->bCanBeCompleted = !bKeepObjectivesOrder || i == 0;
			Objectives[i]->OnObjectiveCompleted.AddUObject(this, &ThisClass::OnObjectiveCompleted);
		}
	}
	bIsTaken = true;
}

void AQuests::UpdateLocation()
{
	AActor * ParentActor = GetAttachParentActor();
	if (ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

#if WITH_EDITOR
void AQuests::AddLocationObjective()
{
	Objectives.Add(NewObject<ULocationObjective>(this));

}

void AQuests::AddInteractObjective()
{
	Objectives.Add(NewObject<UInteractionObjective>(this));

}
#endif

