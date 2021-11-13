// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

class USaveManager;
UCLASS()
class TANKGEDDON_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:

	void Init() override;

	UFUNCTION(BlueprintCallable, meta=(WorldContext = WorldContextObjet))
	static USaveManager* GetSaveManager(UObject* WorldContextObjet);
	
	protected:
	USaveManager* SaveManager;
	
};
