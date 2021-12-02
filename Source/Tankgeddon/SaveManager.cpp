// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"

#include "TestSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "XmlParser/Public/XmlFile.h"

void USaveManager::Init()
{
	CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));

	//=========================== ++  lesson 8 / plugins
	const FString SlotsPath = FPaths::ProjectSavedDir() + "SaveGames/Slots.txt";
				
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FileManager.FileExists(*SlotsPath))
	{
		if (FFileHelper::LoadFileToStringArray(CurrentSlots, *SlotsPath))
		{
			for (const auto& Slot : CurrentSlots)
			{
				GLog->Log(ELogVerbosity::Warning, TEXT("SaveManager::Init, slot: ") + Slot);
			}

		}
		
	}	
	//=========================== -- lesson 8 / plugins 
}
  
bool USaveManager::DoesSaveGameExist(const FString& SlotName)
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

//============= LOAD
void USaveManager::LoadGame(const FString& SlotName)
{
		
	if (!DoesSaveGameExist(SlotName))
	{
		return;
	}
	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	
	LoadDelegate.BindUObject(this, &ThisClass::OnGameLoadedFunc);
	
	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0,LoadDelegate);	
}


//============= SAVE
void USaveManager::SaveGame(const FString& SlotName)
{
	FAsyncSaveGameToSlotDelegate SaveDelegate;
	
	SaveDelegate.BindUObject(this, &ThisClass::OnGameSavedFunc);
	
	UGameplayStatics::AsyncSaveGameToSlot(CurrentGameObject, SlotName, 0, SaveDelegate);
	
}


//=========================== ++  lesson 8 / plugins
TArray<FString> USaveManager::GetCurrentSlots() const
{
	TArray<FString> TempSlots;
	 
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FileManager.FindFiles(TempSlots, *FPaths::ProjectSavedDir(), TEXT (".sav"));
	return TempSlots;
}



void USaveManager::SaveCurrentSlots() const
{
	const FString SlotsPath = FPaths::ProjectSavedDir() + "SaveGames/Slots.txt";
	
		if (FFileHelper::SaveStringArrayToFile(CurrentSlots, *SlotsPath))
		{
			GLog->Log(ELogVerbosity::Warning, TEXT("SaveManager::Init, save succsess"));
		}		
	
}

void USaveManager::CreateXml(const FString & ContentToSave)
{
	const FString XmlContent = "<DocumentElement>\n<Infor>\n<testfloat>0</testfloat>\n</Infor>\n</DocumentElement>";

	MyXml = new FXmlFile(XmlContent, EConstructMethod::ConstructFromBuffer);


	FXmlNode* _RootNode = MyXml->GetRootNode();
		
	const TArray<FXmlNode*> _AssetNodes = _RootNode->GetChildrenNodes();
		
	for (FXmlNode* node : _AssetNodes)
	{
		//Get all child nodes under _AssetNodes
		const TArray<FXmlNode*> _ChildNodes = node->GetChildrenNodes();

			
		FString _AssetContent = node->GetContent();
			
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, _AssetContent);
			
		for (FXmlNode* xnode : _ChildNodes)
		{
			xnode->SetContent(ContentToSave);
			FString _ChildContent = xnode->GetContent();
			//Print _ChildNodes content
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, _ChildContent);
		}       
	}
	
	
	if (MyXml == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("Failed to create xml file!"));       
		return;
	}
	
	//Save the xml file to the current project
	MyXml->Save(FPaths::ProjectSavedDir() + "SaveGames/MyXML.xml");
	GLog->Log(ELogVerbosity::Error, TEXT("Create xml file successfully!"));
}

FString USaveManager::ParseXml()
{
	// Необходимо проверить существование файла.
	FString MyFile = FPaths::ProjectSavedDir() + "SaveGames/MyXML.xml";

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	
	if (FileManager.FileExists(*MyFile))
	{
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: File found!"));
		
		FXmlFile* XmlFile = new FXmlFile(MyFile);
	
		FXmlNode* _RootNode = XmlFile->GetRootNode();
		
		const TArray<FXmlNode*> _AssetNodes = _RootNode->GetChildrenNodes();
		
		for (FXmlNode* node : _AssetNodes)
		{
			//Get all child nodes under _AssetNodes
			const TArray<FXmlNode*> _ChildNodes = node->GetChildrenNodes();

			
			FString _AssetContent = node->GetContent();
			
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, _AssetContent);
			
			for (FXmlNode* xnode : _ChildNodes)
			{
				FString _ChildContent = xnode->GetContent();
				//Print _ChildNodes content
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, _ChildContent);
				return  _ChildContent;
			}       
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("FilePaths: File not found!"));
		return MyContent;
	}
	return MyContent;
}

//=========================== --  lesson 8 / plugins





void USaveManager::OnGameLoadedFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentGameObject = Cast<UTestSaveGame>(SaveGame);
	OnGameLoaded.Broadcast(SlotName);

}

void USaveManager::OnGameSavedFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	//=========================== ++  lesson 8 / plugins
	if (!CurrentSlots.Contains(SlotName))
	{
		CurrentSlots.AddUnique(SlotName);
		SaveCurrentSlots();
	}	
	//=========================== --  lesson 8 / plugins
	
	OnGameSaved.Broadcast(SlotName);	
}







