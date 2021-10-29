// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

#include "InteractableActor.h"

// Add default functionality here for any IInteractableObject functions that are not pure virtual.
void IInteractableObject::NotifyInteractionFinished(AActor* InteractableObject, AActor* ActorInteractedWithObject)
{	
		OnInteractionFinished.Broadcast(InteractableObject, ActorInteractedWithObject);	
}

void AInteractableActor::OnInteractionFinished(AActor* ActorInteractedWithObject)
{
	NotifyInteractionFinished(this, ActorInteractedWithObject);
}
