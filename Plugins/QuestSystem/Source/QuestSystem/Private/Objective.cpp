// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "InteractableObject.h"
#include "LocationMarker.h"


UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Ot_Interact;

}

void UInteractionObjective::ActivateObjective(AActor* Instigator)
{
	
	if (IInteractableObject * InteractableTarget = Cast<IInteractableObject>(Target))
	{
		InteractableTarget->OnInteractionFinished.AddLambda([this, Instigator](	AActor* InteractableObject, AActor* ActorInteractedWithObject)
		{
			if (bCanBeCompleted && Instigator == ActorInteractedWithObject)
			{
				bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}

	
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Ot_Interact;
}

void ULocationObjective::ActivateObjective(AActor* Instigator)
{
	if (ILocationMarker * LocMarker = Cast<ILocationMarker>(Marker))
	{
		LocMarker->OnLocationReached.AddLambda([this, Instigator](AActor* LocationMarker, AActor* OverlappedActor)
		{
			if (bCanBeCompleted && Instigator == OverlappedActor)
			{
				bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}

}
