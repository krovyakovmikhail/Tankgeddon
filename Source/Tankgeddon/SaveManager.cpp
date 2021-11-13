// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"

#include "TestSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USaveManager::Init()
{
CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));	
}

bool USaveManager::DoesSaveGameExist(const FString& SlotName)
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

void USaveManager::LoadGame(const FString& SlotName)
{
	CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

void USaveManager::SaveGame(const FString& SlotName)
{
	UGameplayStatics::SaveGameToSlot(CurrentGameObject, SlotName, 0);
}



