// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveManager.generated.h"

class UTestSaveGame;
/**
 * 
 */
UCLASS()
class TANKGEDDON_API USaveManager : public UObject
{
	GENERATED_BODY()
	
	public:
        void Init();	
        UFUNCTION(BlueprintCallable)
        bool DoesSaveGameExist(const FString& SlotName);
        UFUNCTION(BlueprintCallable)
        void LoadGame(const FString& SlotName);
        UFUNCTION(BlueprintCallable)
        void SaveGame(const FString& SlotName);
    
    protected:
        UPROPERTY(BlueprintReadWrite)
        UTestSaveGame * CurrentGameObject;

};
