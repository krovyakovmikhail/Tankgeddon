// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
	Super::Init();

	
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init()"));

	SaveManager = NewObject<USaveManager>(this);
	SaveManager->Init();
}

USaveManager* UMyGameInstance::GetSaveManager(UObject* WorldContextObjet)
{
	UMyGameInstance * myInstanse = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObjet));

	if (myInstanse)
	{
		return myInstanse->SaveManager;
	}
		return nullptr;
}
