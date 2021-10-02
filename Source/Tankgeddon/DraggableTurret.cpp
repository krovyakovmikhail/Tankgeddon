// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableTurret.h"

void UDraggableTurret::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (TurretNameText)
    {
        TurretNameText->SetText(TurretName);
    }
}