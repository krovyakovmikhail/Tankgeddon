// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quests.h"
#include "Blueprint/UserWidget.h"
#include "CurrentObjectives.generated.h"

class UVerticalBox;
class UObjectiveWidget;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UCurrentObjectives : public UUserWidget
{
	GENERATED_BODY()

	public:
	UFUNCTION()
	void SetCurrentObjectives(AQuests * Quest);
    
	protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	UVerticalBox * ObjectivesList;

};
