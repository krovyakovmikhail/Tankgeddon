// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "SaveManager.generated.h"


class UTestSaveGame;
class USaveGame;
/**
 * 
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveAction, const FString&, SlotName);

UCLASS()
class TANKGEDDON_API USaveManager : public UObject
{
	GENERATED_BODY()
	
	public:
	
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnSaveAction OnGameLoaded;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnSaveAction OnGameSaved;

        void Init();	
        UFUNCTION(BlueprintPure)
        bool DoesSaveGameExist(const FString& SlotName);
        UFUNCTION(BlueprintCallable)
        void LoadGame(const FString& SlotName);
        UFUNCTION(BlueprintCallable)
        void SaveGame(const FString& SlotName);
	
	 // Plugins  / leson 8 ++
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetCurrentSlots() const;
	
	UFUNCTION(BlueprintCallable)
	void CreateXml(const FString & ContentToSave);
	UFUNCTION(BlueprintPure)
	FString ParseXml();
	// Plugins  / leson 8 --
    
    protected:

		
		
	
        UPROPERTY(BlueprintReadWrite)
        UTestSaveGame * CurrentGameObject;
	
		// Plugins  / leson 8 +
		FXmlFile * MyXml;

		FString MyContent = "";
		// Plugins  / leson 8 --
	
        
		void OnGameLoadedFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);
		void OnGameSavedFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	

	TArray<FString> CurrentSlots;
	void SaveCurrentSlots() const;
	

};
