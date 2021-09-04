// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "GameStructs.generated.h"

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()

		UPROPERTY()
		float DamageValue;
	UPROPERTY()
		AActor* Instigator;
	UPROPERTY()
		AActor* DamageMaker;
};

UENUM(BlueprintType)
enum class ECannonType : uint8 {
    FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
    FireTrace = 1  UMETA(DisplayName = "Use trace"),
    FireAuto = 2  UMETA(DisplayName = "Use autofire")
};