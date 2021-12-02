// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "GameFramework/SaveGame.h"
#include "TestSaveGame.generated.h"

/**
 * 
 */



UCLASS()
class TANKGEDDON_API UTestSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	public:
        UPROPERTY(BlueprintReadWrite)
        float TestFloat;
	
		UPROPERTY(BlueprintReadWrite) 
		float CurrentHealthPlayerPawn; // 
	
		UPROPERTY(BlueprintReadWrite)
		float CurrentHealthAIPawn;
	
		UPROPERTY(BlueprintReadWrite)
		FVector CurrentLocationPlayerPawn;
	
	UPROPERTY(BlueprintReadWrite)
	FVector CurrentLocationAITAnk;
	
		UPROPERTY(BlueprintReadWrite)
		ACannon * CurrentCannonOnTank;
	
		UPROPERTY(BlueprintReadWrite)
		int32 CurrentShells;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ACannon> CannonClass;
	
	
	
};
