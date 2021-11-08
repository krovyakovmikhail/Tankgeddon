﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWidget.h"

#include "Objective.h"
#include "Components/CheckBox.h"
#include "Components/TExtBlock.h"

void UObjectiveWidget::Init(UObjective* Objective)
{

	if (Objective)
	{
		if (ComplitionCheck)
		{
			ComplitionCheck->SetIsChecked(Objective->bIsCompleted);
		}
		if (DescriptionText)
		{
			DescriptionText->SetText(Objective->Descrition);
		}
	}


	
}
