// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "TurretDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class TANKGEDDON_API UTurretDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:

	FText TurretName;
};
