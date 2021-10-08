// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "TurretAssistant.generated.h"

/**
 * 
 */
UCLASS()
class TANKGEDDON_API ATurretAssistant : public ATurret
{
	GENERATED_BODY()
	public:
	bool IsPlayerInRange();
	bool IsPlayerSeen();
};

